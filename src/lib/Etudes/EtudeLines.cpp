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

#include <glm/gtc/constants.hpp>

#include "Render/ModulationFuncs.hpp"

#include "EtudeLines.hpp"


namespace etudes {
    using glm::pi;
    using glm::vec2;
    using glm::vec3;

    EtudeLines::EtudeLines() {
        registerInput("distance/amplitude");
        registerInput("distance/frequency");
    }

    EtudeLines::~EtudeLines() {

    }    
    
    void EtudeLines::draw() {
        int numLines = 200;

        float amp = getValue("distance/amplitude");
        float freq = getValue("distance/frequency");
        
        render.drawParallels(
            vec2(-1, -1),
            vec2( 1,  1),
            numLines, numLines,
            funcConst(2), // width
            // distance:
            funcSin(amp,
                    0.005f, // phase
                    freq*2.0f*pi<float>()/numLines),
            funcConst(vec3(1,1,1)) // color
            );
    }

    std::string EtudeLines::whoami() {
        return "Lines";
    }
}
