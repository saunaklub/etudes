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

#include <glbinding/gl/gl.h>

#include <Utility/Utility.hpp>
#include <Graphics/Context.hpp>

#include "Truchet.hpp"

namespace etudes {

    using namespace gl;

    Truchet::Truchet() :
        quad(-1, -1, 1, 1)
    {}

    void Truchet::init() {
        ShaderRegistry & shaders = getShaderRegistry();

        shaders.registerShader("truchet", GL_FRAGMENT_SHADER,
                               {"resources/shaders/elements/truchet.frag"});

        shaders.registerProgram("truchet", {"ident", "truchet"});
        shaders.registerUniform("truchet", "time");
        shaders.registerUniform("truchet", "resolution");

        shaders.registerUniform("truchet", "colorSurface");

        shaders.registerUniform("truchet", "foldFactor");
    }

    void Truchet::registerInputs() {
        registerInput("color-surface", vec_float_t{1.f, .05f, 1.f});
        registerInput("fold", vec_float_t{6.3f});
    }

    void Truchet::update() {
        colorSurface = getValue<glm::vec3>("color-surface");
        foldFactor = getValue<float>("fold");
    }

    void Truchet::draw() {
        Rect viewport = getContext().getViewport2D();
        ShaderRegistry & shaders = getShaderRegistry();

        glUseProgram(shaders.getProgram("truchet"));
        glUniform2f(shaders.getUniform("truchet", "resolution"),
                    viewport.getWidth(), viewport.getHeight());
        glUniform1f(shaders.getUniform("truchet", "time"), util::seconds());

        glUniform3f(shaders.getUniform("truchet", "colorSurface"),
                    colorSurface[0], colorSurface[1], colorSurface[2]);

        glUniform1f(shaders.getUniform("truchet", "foldFactor"),
                    foldFactor);

        quad.draw();
    }
}
