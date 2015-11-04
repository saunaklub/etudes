#include <iostream>
#include <iomanip>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Etudes/EtudeTriangles.hpp"
#include "Etudes/EtudeLines.hpp"

#include "Input/OSCInput.hpp"

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
        for(auto etude : etudes) {
            delete etude;
        }
    }

    bool EtudesHost::initialise() {
        bool success = true;

        success &= initGLFW();
        success &= initOSC();
        success &= initEtudes();
        
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
	return true;
    }
    
    bool EtudesHost::initOSC() {
        etudes::OSCInput source(6666);
        return source.start();
	
    }

    bool EtudesHost::initEtudes() {
        etudes.push_back(new EtudeLines());
        etudes.push_back(new EtudeTriangles());
        curEtude = etudes.begin();

        printEtude();

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

    void EtudesHost::nextEtude() {
        curEtude++;
        if(curEtude == etudes.end())
            curEtude = etudes.begin();
    }

    void EtudesHost::prevEtude() {
        if(curEtude == etudes.begin())
            curEtude = etudes.end();
        curEtude--;
    }

    void EtudesHost::printEtude() {
        int index = curEtude - etudes.begin();

        std::cout << "Étude "
                  << std::setfill('0') << std::setw(2) << index << ": "
                  << (*curEtude)->name() << std::endl;
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
        
        (*curEtude)->draw();
        
        glfwSwapBuffers(window);
    }
}
