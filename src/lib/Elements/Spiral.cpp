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

#include <glbinding/gl/gl.h>

#include <Utility/Utility.hpp>
#include <Graphics/Context.hpp>

#include "Spiral.hpp"

namespace etudes {

    using namespace gl;

    Spiral::Spiral() :
        quad(-1, -1, 1, 1)
    {}

    void Spiral::registerInputs() {
        registerInput("curl",    vec_float_t{0.0f});
    }

    void Spiral::draw() {
        const ShaderRegistry & registry = getContext().getShaderRegistry();

        float curl = getValue<float>("curl");

        glUseProgram(registry.getProgram("spiral"));
        glUniform1f(registry.getUniform("spiral", "time"), util::seconds());
        glUniform1f(registry.getUniform("spiral", "curl"), curl);

        quad.draw();
    }
}
