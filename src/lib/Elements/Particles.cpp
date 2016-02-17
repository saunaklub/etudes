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
        registerInput("/count", {10});
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
        vec2 center = to_vec2(getValue<vecf>("/center"));

        size_t indexMin = 0;
        float distMin = std::numeric_limits<float>::max();
        for(size_t index = 0 ; index < positions.size() ; ++index) {
            vec2 dist = positions[index] - center;
            float product = dot(dist, dist);
            if(product < distMin) {
                distMin = product;
                indexMin = index;
            }
        }

        vec2 gbest = positions[indexMin];

        float phi_cognitive = 2.0;
        float phi_social = 2.1;
        float w = 0.72984f;
//        float w = 0.87;
//        float w = 0.02;

        // update velocities and positions
        std::uniform_real_distribution<float> distU;
        for(size_t index = 0 ; index < positions.size() ; ++index) {
            float rand1 = distU(randGen);
            float rand2 = distU(randGen);

            vec2 ibest(positions[index]);
            vec2 deltaV =
                (phi_cognitive * rand1 * (ibest - positions[index]) +
                 phi_social    * rand2 * (gbest - positions[index]));

            // float maxDot = 0.0002f;
            // if(dot(deltaV, deltaV) > maxDot)
            //     deltaV = maxDot * normalize(deltaV);

            velocities[index] = w * (velocities[index] + deltaV);
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
        glLineWidth(5.0f);
        glDrawArrays(GL_POINTS, 0, positions.size());
    }

}
