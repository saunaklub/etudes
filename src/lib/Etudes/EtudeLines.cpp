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
        registerInput("width", 5.0f);
        registerInput("distance/amplitude", 0.1f);
        registerInput("distance/frequency", 0.01f);
    }

    EtudeLines::~EtudeLines() {

    }    
    
    void EtudeLines::draw() {
        int numLines = 200;

        float amp = getValue("distance/amplitude");
        float freq = getValue("distance/frequency");

        auto dist = funcConst(0.05);
        auto width = funcSin(5, 5, 1.0, 0.2);

        float gCenter = 0.7f;
        float gAmplit = 0.3f;
        auto color = funcSin(vec3(0, 0.7, gCenter),
                             vec3(0, 0, gAmplit),
                             2, 0.1f);

        render.drawParallels(
            vec2(0.5, -1),
            vec2(0.5,  1),
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
