/*

  Études Audiovisuelles - Graphical elements for audiovisual composition.
  Copyright (C) 2015-2016 Patric Schmitz

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

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>
#include <Utility/Configuration.hpp>

#include <Factories/SceneFactory.hpp>
#include <Receivers/Scene.hpp>

#include <IO/OSCInput.hpp>

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

    using util::checkGLError;

    void error_callback(int error, const char * description) {
        std::cerr << description << std::endl;
    }

    void key_callback(
        GLFWwindow* window,
        int key, int scancode, int action, int mods) {
        static_cast<EtudesHost*>(glfwGetWindowUserPointer(window))
            ->keyCallback(key, scancode, action, mods);
    }

    void window_size_callback(GLFWwindow* window, int width, int height) {
        static_cast<EtudesHost*>(glfwGetWindowUserPointer(window))
            ->resizeCallback(width, height);
    }

    EtudesHost::EtudesHost() :
        logFramerate(false),
        vsync(false),
        viewportScaling(Rect::Scaling::CROP),
        window(nullptr),
        paused(false),
        quitLoop(false),
        oscInput(6666) {
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
        initOSC();
        initScenes();
        initInput();
    }

    void EtudesHost::initGLFW() {
        glfwSetErrorCallback(error_callback);

        if(!glfwInit()) {
            throw std::runtime_error("glfwInit failed");
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if(hostConfig.hasValue("window:multisampling")) {
            int multisampling =
                hostConfig.getValue<int>("window:multisampling");
            glfwWindowHint(GLFW_SAMPLES, multisampling);
        }

        std::string title;
        if(hostConfig.hasValue("window:title")) {
            title = hostConfig.getValue<std::string>("window:title");
        }
        else {
            title = "Études audiovisuelles";
        }

        GLFWmonitor * monitor = nullptr;
        int width = hostConfig.getValue<int>("viewport:width");
        int height = hostConfig.getValue<int>("viewport:height");

        if(hostConfig.hasValue("window:fullscreen") &&
           hostConfig.getValue<bool>("window:fullscreen")) {

            monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode * mode = glfwGetVideoMode(monitor);

            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

            width = mode->width;
            height = mode->height;
        }
        else {
        }

        window = glfwCreateWindow(width, height, title.c_str(),
                                  monitor, nullptr);
        if(window == nullptr){
            glfwTerminate();
            throw std::runtime_error("glfwCreateWindow failed");
        }

        if(hostConfig.hasValue("window:cursor")) {
            cursor = hostConfig.getValue<bool>("window:cursor");
            setCursorEnabled(cursor);
        }
        glfwSetWindowUserPointer(window, this);

        glfwMakeContextCurrent(window);
        glbinding::Binding::initialize();

        if(hostConfig.hasValue("window:vsync")) {
            vsync = hostConfig.getValue<bool>("window:vsync");
        }
        glfwSwapInterval(vsync);

        glfwSetKeyCallback(window, key_callback);
        glfwSetWindowSizeCallback(window, window_size_callback);
    }

    void EtudesHost::initGL() {
        printOpenGLInfo();

        context = std::make_unique<Context>();
        context->init();
        checkGLError("host: init context");

        if(hostConfig.hasValue("viewport:scaling")) {
            std::string viewportString =
                hostConfig.getValue<std::string>("viewport:scaling");

            if(viewportString == "stretch") {
                viewportScaling = Rect::Scaling::STRETCH;
            }
            else if(viewportString == "crop") {
                viewportScaling = Rect::Scaling::CROP;
            }
            else if(viewportString == "border") {
                viewportScaling = Rect::Scaling::BORDER;
            }
        }

        int width = hostConfig.getValue<int>("viewport:width");
        int height = hostConfig.getValue<int>("viewport:height");
        resizeCallback(width, height);

        checkGLError("host: initGL");
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

        GLint maxUniformLocations;
        glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &maxUniformLocations);
        output += "  max uniform locations: " +
            std::to_string(maxUniformLocations) + "\n";

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

    void EtudesHost::initScenes() {
        std::list<std::string> sceneList =
            hostConfig.getValue<std::list<std::string>>("scenes");

        for(auto &sceneName : sceneList) {
            Configuration sceneConfig;

            try {
                sceneConfig.read("configuration/scenes/" + sceneName + ".yml");
            }
            catch(std::runtime_error &e) {
                continue;
            }

            auto scene = SceneFactory::makeScene(sceneName, sceneConfig);
            scene->init();
            scene->setContext(*context.get());

            checkGLError(sceneName + " init");

            oscInput.addReceiver(sceneName, scene.get());

            auto renderer =
                std::make_unique<Renderer>(sceneName, std::move(scene));

            if(sceneConfig.hasValue("output")) {
                if(!sceneConfig.hasValue("output:enabled") ||
                   sceneConfig.getValue<bool>("output:enabled")) {
                    log(LogLevel::debug,
                        "Creating video output for '" + sceneName + "'");
                    renderer->setOutput(
                        sceneConfig.getValue<std::string>("output:name"),
                        sceneConfig.getValue<int>("output:width"),
                        sceneConfig.getValue<int>("output:height"));
                }
            }

            renderers.push_back(std::move(renderer));
        }

        currentRenderer = renderers.begin();
        printCurrentRenderer();
    }

    void EtudesHost::initInput() {
        using std::string;
        using std::list;

        if(!hostConfig.hasValue("input"))
            return;

        // Configuration inputConfig = hostConfig.getSubTree("input");
        // if(inputConfig.hasValue("mouse")) {
        //     if(inputConfig.hasValue("mouse:xy")) {
        //         for(auto &e : inputConfig.getValue<list<string>>("mouse:xy"))
        //             inputsMouse.push_back(std::make_pair(MOUSE_XY, e));
        //     }
        // }
    }

    void EtudesHost::resizeCallback(int width, int height) {
        Rect window(0, 0, width, height);
        Rect viewport(0, 0,
                      hostConfig.getValue<int>("viewport:width"),
                      hostConfig.getValue<int>("viewport:height"));
        Rect projection;

        switch(viewportScaling) {
        case Rect::Scaling::STRETCH:
            projection = viewport;
            break;
        case Rect::Scaling::CROP:
            projection = window.resizedTo(viewport, Rect::Scaling::BORDER);
            break;
        case Rect::Scaling::BORDER:
            projection = window.resizedTo(viewport, Rect::Scaling::CROP);
            break;
        }

        context->setViewport2D(viewport);
        context->setProjection2D(projection);
    }


    bool EtudesHost::loopIteration() {
        processInput();

        if(paused)
            return true;

        if(quitLoop)
            return false;

        for(auto &renderer : renderers)
            renderer->update();

        render();

        checkGLError("after main loop");

        if(logFramerate)
            printFramerate();

        return true;
    }

    void EtudesHost::printFramerate() {
        static int  framesFPS = 0;
        static long t0 = util::microSeconds();

        long timeCurrent = util::microSeconds();
        long timeElapsed = (timeCurrent - t0);
        if (timeElapsed >= 1000000) {
            log(LogLevel::info, "rendering at " +
                std::to_string(framesFPS) + " fps");
            t0 = timeCurrent;
            framesFPS = 0;
        }

        framesFPS++;
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

        // float mouseXNorm =  mouseX / width;
        // float mouseYNorm = -mouseY / height;

        // for(auto &inputMouse : inputsMouse) {
        //     switch(inputMouse.first) {
        //     case MOUSE_X:
        //         oscInput.update(inputMouse.second,
        //                         Receiver::vec_float_t{mouseXNorm});
        //         break;
        //     case MOUSE_Y:
        //         oscInput.update(inputMouse.second,
        //                         Receiver::vec_float_t{mouseYNorm});
        //         break;
        //     case MOUSE_XY:
        //         oscInput.update(inputMouse.second,
        //                         Receiver::vec_float_t{mouseXNorm, mouseYNorm});
        //         break;
        //     }
        // }
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
                nextRenderer();
                printCurrentRenderer();
                break;

            case GLFW_KEY_P:
                prevRenderer();
                printCurrentRenderer();
                break;

            case GLFW_KEY_F:
                logFramerate = !logFramerate;
                log(LogLevel::excessive, "framerate display: " +
                    std::to_string(logFramerate));
                break;

            case GLFW_KEY_V:
                vsync = !vsync;
                log(LogLevel::debug, "vertical sync: " +
                    std::to_string(vsync));
                glfwSwapInterval(vsync);
                break;

            case GLFW_KEY_C:
                cursor = !cursor;
                log(LogLevel::debug, "cursor visible: " +
                    std::to_string(cursor));
                setCursorEnabled(cursor);
                break;

            case GLFW_KEY_PAUSE:
                paused = !paused;
                break;
            }
        }
    }

    void EtudesHost::setCursorEnabled(bool enabled) {
        if(enabled)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void EtudesHost::nextRenderer() {
        ++currentRenderer;
        if(currentRenderer == renderers.end())
            currentRenderer = renderers.begin();
    }

    void EtudesHost::printCurrentRenderer() {
        log(LogLevel::info, "Switched to renderer: " + (*currentRenderer)->getName());
    }

    void EtudesHost::prevRenderer() {
        if(currentRenderer == renderers.begin())
            currentRenderer = renderers.end();
        --currentRenderer;
    }

    void EtudesHost::render() {
        renderOutputs();
        renderScreen();
    }

    void EtudesHost::renderOutputs() {
        for(auto &renderer : renderers) {
            renderer->renderOutput();
            checkGLError("drawing " + renderer->getName());
        }
    }

    void EtudesHost::renderScreen() {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);

        (*currentRenderer)->render();
        checkGLError("drawing " + (*currentRenderer)->getName());

        glfwSwapBuffers(window);
    }

}
