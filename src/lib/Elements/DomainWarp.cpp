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

#include <glm/ext.hpp>

#include <Utility/Utility.hpp>
#include <Graphics/Context.hpp>

#include "DomainWarp.hpp"

namespace etudes {

    using namespace gl;

    DomainWarp::DomainWarp() :
        quad(-1, -1, 1, 1)
    {}

    void DomainWarp::init() {
        ShaderRegistry & shaders = getShaderRegistry();

        shaders.registerShader("domainwarp", GL_FRAGMENT_SHADER,
                               {"resources/shaders/elements/domainwarp.frag"});
        shaders.registerProgram("domainwarp", {"mvp-uv", "domainwarp"});

        shaders.registerUniform("domainwarp", "mvp");
        shaders.registerUniform("domainwarp", "resolution");
        shaders.registerUniform("domainwarp", "time");

        shaders.registerUniform("domainwarp", "lacunarity");
        shaders.registerUniform("domainwarp", "H");
    }

    void DomainWarp::registerInputs() {
        registerInput("lacunarity", vec_float_t{2});
        registerInput("H", vec_float_t{0.26});
    }

    void DomainWarp::draw() {
        ShaderRegistry & shaders = getShaderRegistry();
        const Context & context = getContext();
        Rect viewport = context.getViewport2D();

        glUseProgram(shaders.getProgram("domainwarp"));

        glUniform2i(shaders.getUniform("domainwarp", "resolution"),
                    viewport.getWidth(), viewport.getHeight());
        glUniform1f(shaders.getUniform("domainwarp", "time"), util::seconds());

        glUniform1f(shaders.getUniform("domainwarp", "lacunarity"),
                    getValue<float>("lacunarity"));
        glUniform1f(shaders.getUniform("domainwarp", "H"),
                    getValue<float>("H"));

        glm::mat4 model(
            viewport.getWidth(),  0, 0, 0,
            0, viewport.getHeight(), 0, 0,
            0, 0, 1, 0,
            viewport.getX(), viewport.getY(), 0, 1);
        glm::mat4 mvp = getContext().getProjection2D() * model;

        GLint locMVP = shaders.getUniform("domainwarp", "mvp");
        glUniformMatrix4fv(locMVP, 1, GLboolean(false), glm::value_ptr(mvp));

        quad.draw();
    }
}
