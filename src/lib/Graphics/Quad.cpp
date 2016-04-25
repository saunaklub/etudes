#include "Quad.hpp"

namespace etudes {
    using namespace gl;

    Quad::Quad() {
        createGeometry();
    }

    void Quad::createGeometry() {
        glGenVertexArrays(1, &idVertexArray);
        glBindVertexArray(idVertexArray);

        std::array<float, 12> aCoords = {
            0.0, 1.0, 0.0f,
            0.0, 0.0, 0.0f,
            1.0, 1.0, 0.0f,
            1.0, 0.0, 0.0f,
        };

        glGenBuffers(1, &vboVertex);
        glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
        glBufferData(GL_ARRAY_BUFFER,
                     aCoords.size()*sizeof(GLfloat),
                     aCoords.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        std::array<float, 12> aUV = {
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
        };

        glGenBuffers(1, &vboUV);
        glBindBuffer(GL_ARRAY_BUFFER, vboUV);
        glBufferData(GL_ARRAY_BUFFER,
                     aUV.size()*sizeof(GLfloat),
                     aUV.data(),
                     GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    void Quad::draw() {
        glBindVertexArray(idVertexArray);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);

    }
}
