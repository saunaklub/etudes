/*

  Études Audiovisuelles - Graphical elements for audiovisual composition.
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

#ifndef ETUDES_LINES
#define ETUDES_LINES

#include <glm/vec4.hpp>

#include <Utility/ModulationFuncs.hpp>
#include <Receivers/Element.hpp>

namespace etudes {
    class Lines : public Element {
    public:

        void registerInputs() override;
        void draw() override;

    private:
        FuncSin<float> funcDist;
        FuncSin<float> funcWidth;
        FuncSin<glm::vec4> funcColor;
    };
}

#endif // ETUDES_LINES
