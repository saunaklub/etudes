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

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#include <Utility/Logging.hpp>

#include "DrawPrimitives.hpp"

namespace etudes {
    using std::function;
    using std::vector;
    using std::pair;
    using std::make_pair;

    using glm::vec2;
    using glm::vec3;

    using std::to_string;
    using logging::to_string;

    typedef std::vector<float> vec;

    void drawLine(vec2 p0, vec2 p1,
                  float width, vec3 color) {

        log(logging::none,
            "drawLine called with: "s +
            to_string(p0) + " "s +
            to_string(p1) + " "s +
            to_string(width) + " "s +
            to_string(color));

        glEnable(GL_LINE_SMOOTH);

        glLineWidth(width);
        glColor3f(color.r,
                  color.g,
                  color.b);

        glBegin(GL_LINES);
        glVertex3f(p0.x, p0.y, 0);
        glVertex3f(p1.x, p1.y, 0);
        glEnd();
    }

    void drawParallels(vec2 centerp0, vec2 centerp1,
                       int leftRepeat, int rightRepeat,
                       function<float(int)> funcWidth,
                       function<float(int)> funcDistance,
                       function<vec3(int)>  funcColor) {

        // draw center line
        drawLine(
            centerp0, centerp1,
            funcWidth(0), funcColor(0)
            );

        // vector pointing from p0 -> p1
        vec2 diff = centerp1 - centerp0;

        // rotate left/right
        vec2 left  = glm::normalize(vec2(-diff.y, diff.x));
        vec2 right = -left;

        // create pairs of directions and repeats
        vector<pair<vec2, int>> direction_repeat;
        direction_repeat.push_back(make_pair(left,  leftRepeat));
        direction_repeat.push_back(make_pair(right, rightRepeat));

        // intermediate line endpoints
        vec2 repeatp0;
        vec2 repeatp1;

        // draw lines in each 'direction
        for(auto &dr : direction_repeat) {
            repeatp0 = centerp0;
            repeatp1 = centerp1;
            // 'repeat times
            for(int r = 0 ; r < dr.second ; ++r) {
                repeatp0 += dr.first * funcDistance(r);
                repeatp1 += dr.first * funcDistance(r);
                drawLine(
                    repeatp0, repeatp1,
                    funcWidth(r), funcColor(r)
                    );
            }
        }
    }

}
