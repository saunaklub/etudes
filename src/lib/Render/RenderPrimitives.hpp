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

#ifndef ETUDES_RENDERPRIMITIVES
#define ETUDES_RENDERPRIMITIVES

#include <functional>

#include <glm/glm.hpp>

namespace etudes {

    class RenderPrimitives {
    public:
        void drawLine(glm::vec2 p0, glm::vec2 p1,
                      float width,
                      glm::vec3 color);

        void drawParallels(
            glm::vec2 centerp0, glm::vec2 centerp1,
            int leftRepeat, int rightRepeat,
            std::function<float(int)> funcWidth,
            std::function<float(int)> funcDistance,
            std::function<glm::vec3(int)> funcColor);

    private:
    };

}

#endif // ETUDES_RENDERPRIMITIVES
