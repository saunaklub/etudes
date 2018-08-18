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

#ifndef ETUDES_SHADER
#define ETUDES_SHADER

#include <glow/fwd.hh>

#include <Receivers/Element.hpp>

namespace etudes {
    class Shader : public Element {
    public:
        Shader(std::string filename);

        void init() override;
        void registerInputs() override;
        void draw() override;

    private:
        std::string filename;

        Quad quad;
        glow::SharedProgram program;
    };
}

#endif // ETUDES_SHADER
