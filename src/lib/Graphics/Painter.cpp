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

#include "Painter.hpp"

namespace etudes {
    using std::function;
    using std::vector;
    using std::pair;
    using std::make_pair;

    using glm::vec2;
    using glm::vec4;

    using std::to_string;
    using logging::to_string;

    typedef std::vector<float> vec;

    void Painter::init() {
        shaders.registerShader("ident", GL_VERTEX_SHADER,
                                 {"resources/shader/ident.vert"});
        shaders.registerShader("solid", GL_FRAGMENT_SHADER,
                                 {"resources/shader/solid.frag"});
        shaders.registerProgram("line", {"ident", "solid"});
        shaders.registerUniform("line", "color");

        glGenVertexArrays(1, &vaoLine);
        glBindVertexArray(vaoLine);

        glGenBuffers(1, &vboLine);
        glBindBuffer(GL_ARRAY_BUFFER, vboLine);
        glBufferData(GL_ARRAY_BUFFER,
                     2 * sizeof(vec2),
                     NULL, GL_DYNAMIC_DRAW);

        GLint attribPosition =
            glGetAttribLocation(shaders.getProgram("line"), "position");
        glVertexAttribPointer(attribPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(attribPosition);
    }

    void Painter::drawLine(vec2 p0, vec2 p1,
                           float width, vec4 color) const {

#if 0
        log(logging::excessive,
            "drawLine called with: "s +
            to_string(p0) + " "s +
            to_string(p1) + " "s +
            to_string(width) + " "s +
            to_string(color));
#endif

        glUseProgram(shaders.getProgram("line"));
        glBindVertexArray(vaoLine);

        vec2 positions[2] = {p0, p1};
        glBindBuffer(GL_ARRAY_BUFFER, vboLine);
        glBufferSubData(GL_ARRAY_BUFFER,
                        0, 2 * sizeof(vec2),
                        &positions[0]);


        glUniform4f(shaders.getUniform("line", "color"),
                    color.r, color.g, color.b, color.a);

        glDrawArrays(GL_LINES, 0, 2);
    }

    void Painter::drawParallels(vec2 centerp0, vec2 centerp1,
                       int leftRepeat, int rightRepeat,
                       function<float(int)> funcWidth,
                       function<float(int)> funcDistance,
                       function<vec4(int)>  funcColor) const {

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
