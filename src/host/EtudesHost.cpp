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
        window(nullptr),
        quitLoop(false),
        oscInput(etudes, 6666),
        logFramerate(false) {
    }

    EtudesHost::~EtudesHost() {
    }

    bool EtudesHost::initialise() {
        bool success = true;

        hostConfig.read("configuration/host.yml");

        std::string logLevel =
            hostConfig.getValue<std::string>("logging/logLevel");

        logging::setLogLevelMax(logLevelMap[logLevel]);
        logFramerate = hostConfig.getValue<bool>("logging/framerate");

        success &= initGLFW();
        success &= initEtudes();

        initOSC();

        return success;
    }

    bool EtudesHost::initGLFW() {
        glfwSetErrorCallback(error_callback);

        if(!glfwInit())
            exit(EXIT_FAILURE);

        window = glfwCreateWindow(
            hostConfig.getValue<int>("window/width"),
            hostConfig.getValue<int>("window/height"),
            "Études audiovisuel", NULL, NULL);

        if(window == nullptr){
            glfwTerminate();
            return false;
        }

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetWindowUserPointer(window, this);

        glbinding::Binding::initialize();

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glfwSetKeyCallback(window, key_callback);

        return true;
    }

    void EtudesHost::initOSC() {
        oscInput.start();
    }

    bool EtudesHost::initEtudes() {
        std::list<std::string> etudeList =
            hostConfig.getValue<std::list<std::string>>("etudes");

        for(auto &etude : etudeList) {
            Configuration etudeConfig;
            etudeConfig.read("configuration/etudes/" + etude + ".yml");

            Node node = etudeConfig.getNode("");
            etudes.push_back(
                std::make_pair(etude, EtudeFactory::makeEtude(etude, node)));
            etudes.back().second->init();

#ifdef LINUX
            if(node["output"] && node["output"]["enabled"].as<bool>()) {
                log(LogLevel::debug,
                    "Creating video output for '" + etude + "'");
                std::unique_ptr<VideoOutput> out =
                    std::make_unique<VideoOutputV4L2>(
                        etudes.back().second.get(),
                        node["output"]["width"].as<int>(),
                        node["output"]["height"].as<int>());
                out->createOutput(node["output"]["name"].as<std::string>());
                videoOutputs.push_back(std::move(out));
            }
#endif
        }

        currentEtude = etudes.begin();

        return true;
    }

    bool EtudesHost::loopIteration() {
        long t0 = microSeconds();

        processInput();
        if(quitLoop)
            return false;

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
                break;

            case GLFW_KEY_P:
                prevEtude();
                break;
            }
        }
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
        for(auto &e : etudes)
            e.second->update();

        renderOutputs();
        renderScreen();
    }

    void EtudesHost::renderOutputs() {
        for(auto &output : videoOutputs)
            output->render();
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

        currentEtude->second->draw();

        glfwSwapBuffers(window);
    }

}
