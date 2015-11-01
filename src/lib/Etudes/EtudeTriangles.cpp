#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#include "EtudeTriangles.hpp"

namespace etudes {
    void EtudeTriangles::draw() {
      glBegin(GL_TRIANGLES);
      
      glColor3f(1.f, 0.f, 0.f);
      glVertex3f(-0.6f, -0.4f, 0.f);
      glVertex3f(0.6f, -0.4f, 0.f);
      glVertex3f(0.f, 0.6f, 0.f);
      
      glEnd();
    }

    std::string EtudeTriangles::name() {
        return "Triangles";
    }
}
