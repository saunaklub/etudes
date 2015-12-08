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

#include <iostream>

#include "Render/ModulationFuncs.hpp"

#include "EtudeLines.hpp"


namespace etudes {
    using glm::pi;
    using glm::vec2;
    using glm::vec3;

    EtudeLines::EtudeLines() {
        registerInput("distance/base", 0.1f);
        registerInput("distance/amplitude", 0.1f);
        registerInput("distance/omega", 0.01f);
        registerInput("distance/lambda", 0.01f);

        registerInput("width/base", 0.1f);
        registerInput("width/amplitude", 0.1f);
        registerInput("width/omega", 0.01f);
        registerInput("width/lambda", 0.01f);
    }

    EtudeLines::~EtudeLines() {

    }

    void EtudeLines::draw() {
        int numLines = 200;

        float dist_b = getValue("distance/base");
        float dist_a = getValue("distance/amplitude");
        float dist_o = getValue("distance/omega");
        float dist_l = getValue("distance/lambda");

        float width_b = getValue("width/base");
        float width_a = getValue("width/amplitude");
        float width_o = getValue("width/omega");
        float width_l = getValue("width/lambda");

        auto dist  = funcSin(dist_b, dist_a, dist_o, dist_l);
        auto width = funcSin(width_b, width_a, width_o, width_l);

        float gCenter = 0.7f;
        float gAmplit = 0.3f;
        auto color = funcSin(vec3(0, 0.7, gCenter),
                             vec3(0, 0, gAmplit),
                             0, 0.1);

        render.drawParallels(
            vec2(0, -1),
            vec2(0,  1),
            numLines, numLines,
            width,
            dist,
            color
            );
    }

    std::string EtudeLines::whoami() {
        return "Lines";
    }
}
