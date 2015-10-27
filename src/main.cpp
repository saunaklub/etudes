#include <cstdlib>
#include <cstdio>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "lib/Source/OSCSource.hpp"

static void error_callback(int error, const char * description) {
  fputs(description, stderr);
};

static void key_callback(
  GLFWwindow* window,
  int key, int scancode, int action, int mods) {
  if(key == GLFW_KEY_ESCAPE &&
     action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
}

int main(){
  glfwSetErrorCallback(error_callback); 

  if(!glfwInit())
    exit(EXIT_FAILURE);

  GLFWwindow* window = glfwCreateWindow(640, 480, "Project", NULL, NULL);

  if(window == nullptr){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glbinding::Binding::initialize();

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  glfwSetKeyCallback(window, key_callback);

  etudes::OSCSource source(6666);
  source.start();
  
  while(!glfwWindowShouldClose(window)) {
    /*openGL functions taken from
     * http://igorbarbosa.com/articles/how-to-use-opengl-freeglut-and-cmake/
     * and adapted to a very simple red triangle
     */
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(
      0, 0,
      static_cast<GLsizei>(width),
      static_cast<GLsizei>(height)
      );

    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();

    

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glfwDestroyWindow(window);  
  
  return 0;
}
