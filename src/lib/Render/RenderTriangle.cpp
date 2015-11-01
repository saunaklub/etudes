#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;


#include "RenderTriangle.hpp"

namespace etudes {
    void RenderTriangle::render() {
      glBegin(GL_TRIANGLES);
      
      glColor3f(1.f, 0.f, 0.f);
      glVertex3f(-0.6f, -0.4f, 0.f);
      glVertex3f(0.6f, -0.4f, 0.f);
      glVertex3f(0.f, 0.6f, 0.f);
      
      glEnd();
    }

    std::string RenderTriangle::name() {
        return "RenderTriangle";
    }
}
