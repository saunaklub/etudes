#include <random>

#include <Utility/ShaderRegistry.hpp>

#include "Particles.hpp"

using namespace gl;
using glm::vec2;

namespace etudes {

    using vecf = std::vector<float>;

    Particles::Particles() :
        randGen(randDev()) {
    }

    void Particles::registerInputs() {
        registerInput("/count", {100});
        registerInput("/center", {0, 0});
    }

    void Particles::init() {
        count = getValue<float>("/count");
        center = to_vec2(getValue<vecf>("/center"));

        positions.resize(count);
        velocities.resize(count);

        std::normal_distribution<float> distN(0.0f, 0.2f);
        for(auto &p : positions) {
            p = center + vec2(distN(randGen),
                              distN(randGen));
        }
        for(auto &v : velocities) {
            v = vec2(0, 0);
        }

        registry = std::make_unique<ShaderRegistry>();
        registry->registerShader("ident", GL_VERTEX_SHADER,
                                 {"resources/shader/ident.vert"});
        registry->registerShader("white", GL_FRAGMENT_SHADER,
                                 {"resources/shader/white.frag"});
        registry->registerProgram("simple", {"ident", "white"});

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     positions.size() * sizeof(vec2),
                     NULL, GL_STATIC_DRAW);

        GLint attribPosition =
            glGetAttribLocation(registry->getProgram("simple"), "position");
        glVertexAttribPointer(attribPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(attribPosition);
    }

    void Particles::update() {
        float distMin = std::numeric_limits<float>::max();
        size_t indexMin = 0;
        for(size_t index = 0 ; index < positions.size() ; ++index) {
            float product = dot(positions[index], positions[index]);
            if(product < distMin) {
                distMin = product;
                indexMin = index;
            }
        }
        vec2 gbest = positions[indexMin];

        // update velocities and positions
        std::uniform_real_distribution<float> distU;
        for(size_t index = 0 ; index < positions.size() ; ++index) {
            float rand1 = distU(randGen);
            float rand2 = distU(randGen);

            vec2 ibest(0, 0);
            vec2 deltaV = 0.01f *
                (rand1 * (ibest - positions[index]) +
                 rand2 * (gbest - positions[index]));

            velocities[index] += deltaV;
            positions[index] += velocities[index];
        }

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER,
                        0, positions.size() * sizeof(vec2),
                        &positions[0]);
    }

    void Particles::draw() {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glPointSize(10.0f);
        glDrawArrays(GL_POINTS, 0, positions.size());
    }

}
