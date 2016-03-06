/*

  Études Audiovisuel - graphical elements for audiovisual composition
  Copyright (C) 2015 Patric Schmitz, Claudio Cabral

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <iostream>
#include <iomanip>

#include <yaml-cpp/yaml.h>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <Utility/Logging.hpp>
#include <Utility/Configuration.hpp>
#include <Factories/EtudeFactory.hpp>
#include <Receivers/Etude.hpp>

#include <IO/OSCInput.hpp>
#include <IO/VideoOutputV4L2.hpp>

#include "EtudesHost.hpp"

namespace {
    using YAML::Node;

    using etudes::logging::LogLevel;

    std::map<std::string, LogLevel> logLevelMap = {
        {"none", LogLevel::none},
        {"info", LogLevel::info},
        {"warning", LogLevel::warning},
        {"error", LogLevel::error},
        {"debug", LogLevel::debug},
        {"excessive", LogLevel::excessive}
    };
}

namespace etudes {

    void error_callback(int error, const char * description) {
        std::cerr << description << std::endl;
    };

    void key_callback(
        GLFWwindow* window,
        int key, int scancode, int action, int mods) {
        static_cast<EtudesHost*>(glfwGetWindowUserPointer(window))
            ->keyCallback(key, scancode, action, mods);
    }

    EtudesHost::EtudesHost() :
        logFramerate(false),
        window(nullptr),
        quitLoop(false),
        oscInput(etudes, 6666) {
    }

    EtudesHost::~EtudesHost() {
    }

    void EtudesHost::initialise() {
        hostConfig.read("configuration/host.yml");

        std::string logLevel =
            hostConfig.getValue<std::string>("logging:logLevel");

        logging::setLogLevelMax(logLevelMap[logLevel]);
        logFramerate = hostConfig.getValue<bool>("logging:framerate");

        initGLFW();
        initGL();
        initEtudes();
        initOSC();
        initInput();
    }

    void EtudesHost::initGLFW() {
        glfwSetErrorCallback(error_callback);

        if(!glfwInit()) {
            throw std::runtime_error("glfwInit failed");
        }

        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        window = glfwCreateWindow(
            hostConfig.getValue<int>("window:width"),
            hostConfig.getValue<int>("window:height"),
            "Études audiovisuel", NULL, NULL);

        if(window == nullptr){
            glfwTerminate();
            throw std::runtime_error("glfwCreateWindow failed");
        }

        if(hostConfig.hasValue("window:cursor")) {
            if(!hostConfig.getValue<bool>("window:cursor"))
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        }
        glfwSetWindowUserPointer(window, this);

        glbinding::Binding::initialize();

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glfwSetKeyCallback(window, key_callback);
    }

    void EtudesHost::initGL() {
        printOpenGLInfo();
        painter.init();
    }

    void EtudesHost::printOpenGLInfo() {
        std::string output = "OpenGL information:\n";

        output += "  version string: " +
            std::string((const char*)(glGetString(GL_VERSION))) + "\n";

        GLint maxTexSize, maxTexUnits;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTexUnits);
        output += "  max texture size: " + std::to_string(maxTexSize) + "\n";
        output += "  max texture units: " + std::to_string(maxTexUnits) + "\n";


        std::array<GLfloat, 2> lineWidthRangeAliased;
        std::array<GLfloat, 2> lineWidthRangeSmooth;
        glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, &lineWidthRangeAliased[0]);
        glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, &lineWidthRangeSmooth[0]);
        output += "  line width aliased: " +
            std::to_string(lineWidthRangeAliased[0]) + " - " +
            std::to_string(lineWidthRangeAliased[1]) + "\n";
        output += "  line width smooth:  " +
            std::to_string(lineWidthRangeSmooth[0]) + " - " +
            std::to_string(lineWidthRangeSmooth[1]) + "\n";

        log(LogLevel::info, output);
    }

    void EtudesHost::initOSC() {
        oscInput.start();
    }

    void EtudesHost::initEtudes() {
        std::list<std::string> etudeList =
            hostConfig.getValue<std::list<std::string>>("etudes");

        for(auto &etude : etudeList) {
            Configuration etudeConfig;
            etudeConfig.read("configuration/etudes/" + etude + ".yml");

            etudes.push_back(
                std::make_pair(
                    etude, EtudeFactory::makeEtude(etude, etudeConfig)));
            etudes.back().second->init();

#ifdef LINUX
            if(etudeConfig.hasValue("output")) {
                if(!etudeConfig.hasValue("output:enabled") ||
                   etudeConfig.getValue<bool>("output:enabled")) {
                    log(LogLevel::debug,
                        "Creating video output for '" + etude + "'");
                    std::unique_ptr<VideoOutput> out =
                        std::make_unique<VideoOutputV4L2>(
                            etudes.back().second.get(),
                            etudeConfig.getValue<int>("output:width"),
                            etudeConfig.getValue<int>("output:height"));
                    out->createOutput(
                        etudeConfig.getValue<std::string>("output:name"));
                    videoOutputs.push_back(std::move(out));
                }
            }
#endif
        }

        currentEtude = etudes.begin();
        printEtude();
    }

    void EtudesHost::initInput() {
        using std::string;
        using std::list;

        if(!hostConfig.hasValue("input"))
            return;

        Configuration inputConfig = hostConfig.getSubTree("input");
        if(inputConfig.hasValue("mouse")) {
            if(inputConfig.hasValue("mouse:xy")) {
                for(auto &e : inputConfig.getValue<list<string>>("mouse:xy"))
                    inputsMouse.push_back(std::make_pair(MOUSE_XY, e));
            }
        }
    }

    bool EtudesHost::loopIteration() {
        long t0 = microSeconds();

        processInput();
        if(quitLoop)
            return false;

        for(auto &e : etudes)
            e.second->update();

        render();

        if(logFramerate)
            log(LogLevel::excessive, "rendering at " +
                std::to_string(1000000.0/(microSeconds()-t0)) + " fps");

        return true;
    }

    void EtudesHost::processInput() {
        glfwPollEvents();

        if(glfwWindowShouldClose(window)) {
            glfwDestroyWindow(window);
            quitLoop = true;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        float mouseXNorm =  ((mouseX / width)  - 0.5) * 2.0f;
        float mouseYNorm = -((mouseY / height) - 0.5) * 2.0f;

        for(auto &inputMouse : inputsMouse) {
            switch(inputMouse.first) {
            case MOUSE_X:
                oscInput.update(inputMouse.second, {mouseXNorm});
                break;
            case MOUSE_Y:
                oscInput.update(inputMouse.second, {mouseYNorm});
                break;
            case MOUSE_XY:
                oscInput.update(inputMouse.second, {mouseXNorm, mouseYNorm});
                break;
            }
        }
    }

    void EtudesHost::keyCallback(
        int key, int scancode, int action, int mods) {

        if(action == GLFW_PRESS) {
            switch(key) {

            case GLFW_KEY_ESCAPE:
            case GLFW_KEY_Q:
                glfwSetWindowShouldClose(window, 1);
                break;

            case GLFW_KEY_N:
                nextEtude();
                printEtude();
                break;

            case GLFW_KEY_P:
                prevEtude();
                printEtude();
                break;
            }
        }
    }

    void EtudesHost::printEtude() {
        log(LogLevel::info, "Switched to etude: " + currentEtude->first);
    }

    void EtudesHost::nextEtude() {
        currentEtude++;
        if(currentEtude == etudes.end())
            currentEtude = etudes.begin();
    }

    void EtudesHost::prevEtude() {
        if(currentEtude == etudes.begin())
            currentEtude = etudes.end();
        currentEtude--;
    }

    void EtudesHost::render() {
        renderOutputs();
        renderScreen();
    }

    void EtudesHost::renderOutputs() {
        for(auto &output : videoOutputs)
            output->render(painter);
    }

    void EtudesHost::renderScreen() {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glViewport(
            0, 0,
            static_cast<GLsizei>(width),
            static_cast<GLsizei>(height)
            );

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        currentEtude->second->draw(painter);

        glfwSwapBuffers(window);
    }

}
