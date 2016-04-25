#ifndef ETUDES_QUAD
#define ETUDES_QUAD

#include <glbinding/gl/gl.h>

namespace etudes {
    class Quad {
    public:
        Quad();
        void draw();

    private:
        void createGeometry();

        // @todo: make static?
        gl::GLuint idVertexArray;
        gl::GLuint vboVertex;
        gl::GLuint vboUV;
    };
}

#endif // ETUDES_QUAD

