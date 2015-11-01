#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#include "EtudeLines.hpp"

namespace etudes {
    void EtudeLines::draw() {
        glLineWidth(5);
        glColor3f(0.7, 0.0, 0.7);

        glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(-0.5, 0.5, 0.0);
        glEnd();
    }

    std::string EtudeLines::name() {
        return "Lines";
    }
}
