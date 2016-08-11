/*

  Études Audiovisuels - Graphical elements for audiovisual composition.
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

#ifndef ETUDES_PARTICLES
#define ETUDES_PARTICLES

#include <vector>
#include <random>

#include <glbinding/gl/gl.h>

#include <glm/glm.hpp>

#include <Receivers/Element.hpp>

namespace etudes {
    class Particles : public Element {
    public:
        Particles();

        void registerInputs() override;

        void init() override;
        void update() override;
        void draw() override;

    private:
        void initGL();

        void updateBest();

        gl::GLuint vao, vbo;

        int count;
        glm::vec2 center;

        std::vector<glm::vec2> positions;
        std::vector<glm::vec2> positionsIBest;
        glm::vec2 positionGBest;

        std::vector<glm::vec2> velocities;

        std::random_device randDev;
        std::mt19937 randGen;
    };
}

#endif // ETUDES_PARTICLES
