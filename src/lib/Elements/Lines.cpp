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

#include <glm/gtc/constants.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <Utility/Utility.hpp>

#include <Graphics/Context.hpp>
#include <Graphics/Painter.hpp>
#include <Graphics/Geometry/Transforms.hpp>

#include "Lines.hpp"

namespace etudes {
    using glm::pi;
    using glm::vec2;
    using glm::vec4;

    using util::deg2rad;

    void Lines::registerInputs() {
        registerInput("count", vec_float_t{100.0f});
        registerInput("angle", vec_float_t{0});

        registerInput("distance/base",      vec_float_t{0.1f});
        registerInput("distance/amplitude", vec_float_t{0.0f});
        registerInput("distance/omega",     vec_float_t{0.0f});
        registerInput("distance/lambda",    vec_float_t{0.0f});

        registerInput("width/base",      vec_float_t{5.0f});
        registerInput("width/amplitude", vec_float_t{0.0f});
        registerInput("width/omega",     vec_float_t{0.0f});
        registerInput("width/lambda",    vec_float_t{0.0f});

        registerInput("color/base",      vec_float_t{1.0f, 1.0f, 1.0f, 1.0f});
        registerInput("color/amplitude", vec_float_t{0.0f, 0.0f, 0.0f, 0.0f});
        registerInput("color/omega",     vec_float_t{0.0f});
        registerInput("color/lambda",    vec_float_t{0.0f});
    }

    void Lines::draw() {
        Painter & painter = getPainter();

        auto dist_b = getValue<float>("distance/base");
        auto dist_a = getValue<float>("distance/amplitude");
        auto dist_o = getValue<float>("distance/omega");
        auto dist_l = getValue<float>("distance/lambda");

        auto width_b = getValue<float>("width/base");
        auto width_a = getValue<float>("width/amplitude");
        auto width_o = getValue<float>("width/omega");
        auto width_l = getValue<float>("width/lambda");

        auto color_b = getValue<vec4>("color/base");
        auto color_a = getValue<vec4>("color/amplitude");
        auto color_o = getValue<float>("color/omega");
        auto color_l = getValue<float>("color/lambda");

        funcDist.step(dist_b, dist_a, dist_o, dist_l);
        funcWidth.step(width_b, width_a, width_o, width_l);
        funcColor.step(color_b, color_a, color_o, color_l);

        auto count = getValue<float>("count");
        auto angle = getValue<float>("angle");

        auto p0 = vec2(2.0f*cos(deg2rad(angle)),
                       2.0f*sin(deg2rad(angle)));
        auto p1 = -p0;

        painter.setInputNormalized(true);
        painter.drawParallels(p0, p1,
                              count, count,
                              funcWidth, funcDist, funcColor);
    }
}
