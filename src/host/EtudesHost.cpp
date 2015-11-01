#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Render/Render.hpp"
#include "Render/RenderTriangle.hpp"
#include "Render/RenderLine.hpp"

#include "Source/OSCSource.hpp"

#include "EtudesHost.hpp"

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
        quitLoop(false) {
    }

    EtudesHost::~EtudesHost() {
        for(auto render : renders) {
            delete render;
        }
    }

    bool EtudesHost::initialise() {
        bool success = true;

        success &= initGLFW();
        success &= initOSC();
        success &= initRenderers();
        
        return success;
    }

    bool EtudesHost::initGLFW() {
        glfwSetErrorCallback(error_callback);

        if(!glfwInit())
            exit(EXIT_FAILURE);

        window = glfwCreateWindow(640, 480, "Études audiovisuel", NULL, NULL);
        if(window == nullptr){
            glfwTerminate();
            return false;
        }

        glfwSetWindowUserPointer(window, this);        

        glbinding::Binding::initialize();

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glfwSetKeyCallback(window, key_callback);
    }
    
    bool EtudesHost::initOSC() {
        etudes::OSCSource source(6666);
        source.start();
    }

    bool EtudesHost::initRenderers() {
        renders.push_back(new RenderTriangle());
        renders.push_back(new RenderLine());
        curRender = renders.begin();

        return true;
    }

    bool EtudesHost::loopIteration() {
        processInput();
        if(quitLoop)
            return false;
        
        render();
        
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
                nextRender();
                break;

            case GLFW_KEY_P:
                prevRender();
                break;
            }
        }
    }

    void EtudesHost::nextRender() {
        curRender++;
        if(curRender == renders.end())
            curRender = renders.begin();
    }

    void EtudesHost::prevRender() {
        if(curRender == renders.begin())
            curRender = renders.end();
        curRender--;
    }

    void EtudesHost::render() {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        
        glViewport(
            0, 0,
            static_cast<GLsizei>(width),
            static_cast<GLsizei>(height)
            );

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        (*curRender)->render();
        
        glfwSwapBuffers(window);
    }
}
