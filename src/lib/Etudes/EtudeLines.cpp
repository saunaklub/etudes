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
    
    void EtudeLines::draw() {

        render.drawParallels(
            vec2(-0.5, -0.5),
            vec2( 0.5,  0.5),
            50, 50,
            funcConst(2),          // width
            funcSin(0.01f, 0.005f, pi<float>()/20.0f), // distance
            funcConst(vec3(1,1,1)) // color
            );
    }

    std::string EtudeLines::whoami() {
        return "Lines";
    }
}
