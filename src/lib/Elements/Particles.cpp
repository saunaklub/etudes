#include <random>

#include <Utility/ShaderRegistry.hpp>

#include "Particles.hpp"

using namespace gl;
using glm::vec2;

namespace etudes {

    void Particles::registerInputs() {
        registerInput("/count", {100});
        registerInput("/center", {0, 0});
    }

    void Particles::init() {
        particles.resize(getValue<float>("/count"));

        std::normal_distribution<float> distN(0.0f, 0.2f);
        std::random_device rd;
        std::mt19937 gen(rd());
        for(auto &p : particles) {
            p = vec2(distN(gen), distN(gen));
        }

        registry = std::make_unique<ShaderRegistry>();
        registry->registerShader("ident", GL_VERTEX_SHADER,
                                 {"src/lib/Shader/ident.vert"});
        registry->registerShader("white", GL_FRAGMENT_SHADER,
                                 {"src/lib/Shader/white.frag"});
        registry->registerProgram("simple", {"ident", "white"});

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     particles.size() * sizeof(vec2),
                     &particles[0],
                     GL_STATIC_DRAW);

        GLint attribPosition =
            glGetAttribLocation(registry->getProgram("simple"), "position");
        glVertexAttribPointer(attribPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(attribPosition);
    }

    void Particles::draw() {
        glBindVertexArray(vao);
        glPointSize(10.0f);
        glDrawArrays(GL_POINTS, 0, particles.size());
    }

}
