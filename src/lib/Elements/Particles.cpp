/*

  Études Audiovisuel - Graphical elements for audiovisual composition.
  Copyright (C) 2015-2016 Patric Schmitz

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <random>

#include <Graphics/ShaderRegistry.hpp>

#include "Particles.hpp"

namespace etudes {

    using namespace gl;
    using glm::vec2;

    Particles::Particles() :
        count(0),
        randGen(randDev()) {
    }

    void Particles::registerInputs() {
        registerInput("count", vec_float_t{256});
        registerInput("center", vec_float_t{0, 0});
    }

    void Particles::init() {
        count = getValue<float>("count");
        center = getValue<vec2>("center");

        positions.resize(count);
        positionsIBest.resize(count);
        velocities.resize(count);

        std::normal_distribution<float> distN(0.0f, 0.2f);
        for(auto &p : positions) {
            p = center + vec2(distN(randGen),
                              distN(randGen));
        }
        for(auto &v : velocities) {
            v = vec2(0, 0);
        }

        initGL();
    }

    void Particles::initGL() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     positions.size() * sizeof(vec2),
                     nullptr, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
    }

    void Particles::update() {
        float phi_cognitive = 4.05;
        float phi_social = 4.1 - phi_cognitive;
        float w = 0.72984f;
//        float w = 0.5;
//        float w = 1;
        float minDot = 0.2;
//        float minDim = 0.1;

        updateBest();

        // update velocities and positions
        std::uniform_real_distribution<float> distU;
        for(size_t index = 0 ; index < positions.size() ; ++index) {
            float rand1 = distU(randGen);
            float rand2 = distU(randGen);

            vec2 ibest(positions[index]);
            vec2 deltaV =
                (phi_cognitive * rand1 * (positionsIBest[index] -
                                          positions[index]) +
                 phi_social    * rand2 * (positionGBest  - positions[index]));

            // float maxDot = 0.0002f;
            // if(dot(deltaV, deltaV) > maxDot)
            //     deltaV = maxDot * normalize(deltaV);

            velocities[index] = w * (velocities[index] + deltaV);
            if(dot(velocities[index], velocities[index]) < minDot)
                velocities[index] = minDot * normalize(velocities[index]);
            // for(int dim = 0 ; dim < 2 ; ++dim) {
            //     if(velocities[index][dim] < minDim)
            //         velocities[index][dim] = minDim;
            // }

            positions[index] += 0.08f * velocities[index];
        }

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER,
                        0, positions.size() * sizeof(vec2),
                        &positions[0]);
    }

    void Particles::updateBest() {
        vec2 center = getValue<vec2>("center");

        size_t indexMin = 0;
        float productMin = std::numeric_limits<float>::max();
        for(size_t index = 0 ; index < positions.size() ; ++index) {
            vec2 dist = positions[index] - center;
            vec2 distIBest = positionsIBest[index] - center;

            float product = dot(dist, dist);
            float productIBest = dot(distIBest, distIBest);

            if(product < productIBest) {
                positionsIBest[index] = positions[index];
            }
            if(product < productMin) {
                productMin = product;
                indexMin = index;
            }
        }

        positionGBest = positions[indexMin];
    }

    void Particles::draw() {
        glUseProgram(getContext().getShaderRegistry().getProgram("simple"));

        glBindVertexArray(vao);

        glPointSize(10.0f);
        glDrawArrays(GL_POINTS, 0, positions.size());
    }

}
