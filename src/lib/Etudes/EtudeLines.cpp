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

#include <cmath>
#include <iostream>

#include <glm/gtc/constants.hpp>

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

        auto dist = funcConst(0.1);
        auto width = funcSinT(20, 20, 2.0f*pi<float>());
        auto color = funcSinK(vec3(0,0.7,1));


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
