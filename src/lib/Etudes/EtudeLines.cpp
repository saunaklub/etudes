/*

  Études Audiovisuel - graphical elements for audiovisual composition
  Copyright (C) 2015 Patric Schmitz, Claudio Cabral

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

#include <string>
#include <iostream>

#include <Util/Logging.hpp>
#include <Util/Utilities.hpp>

#include <Drawing/ModulationFuncs.hpp>
#include <Drawing/DrawPrimitives.hpp>

#include "EtudeLines.hpp"

namespace etudes {
    using glm::pi;
    using glm::vec2;
    using glm::vec3;

    typedef std::vector<float> svec;

    EtudeLines::EtudeLines() {
        registerInput("count", {100.0f});
        registerInput("angle", {pi<float>()/2.0f});

        registerInput("distance/base",      {0.1f});
        registerInput("distance/amplitude", {0.0f});
        registerInput("distance/omega",     {0.0f});
        registerInput("distance/lambda",    {0.0f});

        registerInput("width/base",      {5.0f});
        registerInput("width/amplitude", {0.0f});
        registerInput("width/omega",     {0.0f});
        registerInput("width/lambda",    {0.0f});

        registerInput("color/base",      {1.0f, 1.0f, 1.0f});
        registerInput("color/amplitude", {0.0f, 0.0f, 0.0f});
        registerInput("color/omega",     {0.0f});
        registerInput("color/lambda",    {0.0f});
    }

    EtudeLines::~EtudeLines() {

    }

    void EtudeLines::draw() {
        auto dist_b = getValue<float>("distance/base");
        auto dist_a = getValue<float>("distance/amplitude");
        auto dist_o = getValue<float>("distance/omega");
        auto dist_l = getValue<float>("distance/lambda");

        auto width_b = getValue<float>("width/base");
        auto width_a = getValue<float>("width/amplitude");
        auto width_o = getValue<float>("width/omega");
        auto width_l = getValue<float>("width/lambda");

        auto color_b = to_vec3(getValue<svec>("color/base"));
        auto color_a = to_vec3(getValue<svec>("color/amplitude"));
        auto color_o = getValue<float>("color/omega");
        auto color_l = getValue<float>("color/lambda");

        auto dist  = funcSin(dist_b, dist_a, dist_o, dist_l);
        auto width = funcSin(width_b, width_a, width_o, width_l);
        auto color = funcSin(color_b, color_a, color_o, color_l);

        auto count = getValue<float>("count");
        auto angle = getValue<float>("angle");

        auto p0 = vec2(2.0f*cos(angle),
                       2.0f*sin(angle));
        auto p1 = -p0;

        drawParallels(p0, p1,
                      count, count,
                      width, dist, color);
    }

    std::string EtudeLines::whoami() {
        return "Lines";
    }
}
