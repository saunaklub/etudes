/*

  Études Audiovisuelles - Graphical elements for audiovisual composition.
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

#include <array>

#include <Utility/Logging.hpp>

#include "Quad.hpp"

namespace etudes {

    Quad::Quad() {
        createGeometry(-1, 1, 1, -1);
    }

    Quad::Quad(float left, float top,
               float right, float bottom) {
        createGeometry(left, top, right, bottom);
    }

    void Quad::createGeometry(float left, float top,
                              float right, float bottom) {
        glGenVertexArrays(1, &idVertexArray);
        glBindVertexArray(idVertexArray);

        std::array<float, 12> aCoords = {{
                left, top, 0.0f,
                left, bottom, 0.0f,
                right, top, 0.0f,
                right, bottom, 0.0f,
            }};

        glGenBuffers(1, &vboVertex);
        glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
        glBufferData(GL_ARRAY_BUFFER,
                     aCoords.size()*sizeof(GLfloat),
                     aCoords.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        std::array<float, 12> aUV = {{
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
            }};

        glGenBuffers(1, &vboUV);
        glBindBuffer(GL_ARRAY_BUFFER, vboUV);
        glBufferData(GL_ARRAY_BUFFER,
                     aUV.size()*sizeof(GLfloat),
                     aUV.data(),
                     GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glBindVertexArray(0);
    }

    void Quad::draw() const {
        glBindVertexArray(idVertexArray);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }
}
