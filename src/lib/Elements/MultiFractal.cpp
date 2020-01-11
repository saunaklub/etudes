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

#include <glm/ext.hpp>

#include <Utility/Utility.hpp>
#include <Graphics/Context.hpp>

#include "MultiFractal.hpp"

namespace etudes {

    MultiFractal::MultiFractal() :
        quad(-1, -1, 1, 1)
    {}

    void MultiFractal::init() {
        ShaderRegistry & shaders = getShaderRegistry();

        shaders.registerShader("multifractal", GL_FRAGMENT_SHADER,
                               {"resources/shaders/elements/multifractal.frag"});
        shaders.registerProgram("multifractal", {"ident", "multifractal"});

        shaders.registerUniform("multifractal", "resolution");
        shaders.registerUniform("multifractal", "time");

        shaders.registerUniform("multifractal", "zoom");
        shaders.registerUniform("multifractal", "colorBase");
    }

    void MultiFractal::registerInputs() {
        registerInput("zoom", vec_float_t{1});
        registerInput("color-base", vec_float_t{0.2f, 0.4f, 0.8f, 1.0f});
    }

    void MultiFractal::update() {
        zoom = getValue<float>("zoom");
        colorBase = getValue<glm::vec4>("color-base");
    }

    void MultiFractal::draw() {
        ShaderRegistry & shaders = getShaderRegistry();
        const Context & context = getContext();
        Rect viewport = context.getViewport2D();

        glUseProgram(shaders.getProgram("multifractal"));

        glUniform2i(shaders.getUniform("multifractal", "resolution"),
                    viewport.getWidth(), viewport.getHeight());
        glUniform1f(shaders.getUniform("multifractal", "time"),
                    util::seconds());

        glUniform1f(shaders.getUniform("multifractal", "zoom"), zoom);
        glUniform4f(shaders.getUniform("multifractal", "colorBase"),
                    colorBase[0], colorBase[1], colorBase[2], colorBase[3]);

        quad.draw();
    }
}
