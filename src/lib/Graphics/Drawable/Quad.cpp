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

#include <typed-geometry/types/vec.hh>

#include <glow/objects/VertexArray.hh>
#include <glow/objects/ArrayBuffer.hh>

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
        struct Vertex
        {
            tg::vec3 pos;
            tg::vec2 uv;
        };

        std::vector<Vertex> vertices;
        vertices.push_back({tg::vec3(left, top, 0.0f), tg::vec2(0, 1)});
        vertices.push_back({tg::vec3(left, bottom, 0.0f), tg::vec2(0, 0)});
        vertices.push_back({tg::vec3(right, top, 0.0f), tg::vec2(1, 1)});
        vertices.push_back({tg::vec3(right, top, 0.0f), tg::vec2(1, 1)});
        vertices.push_back({tg::vec3(left, bottom, 0.0f), tg::vec2(0, 0)});
        vertices.push_back({tg::vec3(right, bottom, 0.0f), tg::vec2(1, 0)});

        auto ab = glow::ArrayBuffer::create({{&Vertex::pos, "aPos"},
                                             {&Vertex::uv, "aUV"}});
        ab->bind().setData(vertices);
        vertexArray = glow::VertexArray::create(ab);
    }

    void Quad::draw() const {
        vertexArray->bind().draw();
    }
}
