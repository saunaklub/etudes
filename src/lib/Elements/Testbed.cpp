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

#include <Utility/Logging.hpp>

#include <Graphics/Painter.hpp>
#include <Graphics/Geometry/Transforms.hpp>

#include "Testbed.hpp"

namespace etudes {
    using logging::LogLevel;

    void Testbed::registerInputs() {
        registerInput("/test", vec_float_t{});
    }

    void Testbed::draw() {
        auto input = getValue<vec_float_t>("/test");

        const Rect &viewport = getContext().getViewport2D();
        glm::vec2 p0 = denormalize({0.0, 0.5}, viewport);
        glm::vec2 p1 = denormalize({1.0, 0.5}, viewport);

        const Painter & painter = getPainter();
        painter.line(p0, p1, 20, {0, 1, 0, 1});
        painter.line(p0, p1, 1, {1, 0, 0, 1});
    }
}
