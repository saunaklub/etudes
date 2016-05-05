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

#ifndef ETUDES_PAINTER
#define ETUDES_PAINTER

#include <glbinding/gl/gl.h>
#include <glm/glm.hpp>

#include <Graphics/Quad.hpp>

namespace etudes {
    class Context;
    class Painter {
    public:
        Painter(const Context &context);

        void init();

        void line(glm::vec2 p0, glm::vec2 p1,
                  float width, glm::vec4 color) const;

        void sinusoidStraight(
            glm::vec2 p0, glm::vec2 p1, int order,
            float width, glm::vec4 color,
            float time, float freq, float lambda, float phase,
            float strokeWidth, float strokeBlur) const;

        void sinusoidCircular(
            glm::vec2 center, int order,
            float width, float height, glm::vec4 color,
            float time, float freq, float lambda, float phase,
            float circleWidth, float strokeWidth, float strokeBlur) const;

        void parallels(
            glm::vec2 centerp0, glm::vec2 centerp1,
            int leftRepeat, int rightRepeat,
            std::function<float(int)> funcWidth,
            std::function<float(int)> funcDistance,
            std::function<glm::vec4(int)> funcColor,
            bool normalizedInput=false) const;

    private:
        void drawLineGeometry(glm::vec2 p0, glm::vec2 p1,
                              float width, std::string shader) const;
        void drawCircleGeometry(glm::vec2 center, float width, float height,
                                std::string shader) const;

        const Context &context;
        Quad quad;
    };
}

#endif // ETUDES_PAINTER
