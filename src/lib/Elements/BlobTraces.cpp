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
#include <glm/ext.hpp>

#include <Utility/Utility.hpp>
#include <Utility/ModulationFuncs.hpp>

#include <Graphics/Context.hpp>
#include <Graphics/Painter.hpp>

#include "BlobTraces.hpp"

namespace etudes {

    using namespace gl;
    using logging::LogLevel;

    BlobTraces::BlobTraces() {
    }

    void BlobTraces::registerInputs() {
        registerInput("/personA/positionA", vec_float_t{0.5, 0.5});
        registerInput("/personA/positionB", vec_float_t{0.5, 0.5});
        registerInput("/personA/sizeA", vec_float_t{0.5});
        registerInput("/personA/sizeB", vec_float_t{0.5});
    }

    void BlobTraces::init() {
        // Rect viewport = getContext().getViewport2D();

        // width = viewport.getWidth();
        // height = viewport.getHeight();

        // quad = std::make_unique<Quad>();
        // texture = std::make_unique<Texture>(width, height);

        // glGenFramebuffers(1, &idFBO);
        // glBindFramebuffer(GL_FRAMEBUFFER, idFBO);
        // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
        //                        GL_TEXTURE_2D, texture->getId(), 0);
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // shaders.registerShader("algosynth", GL_FRAGMENT_SHADER,
        //                        {"resources/shaders/algosynth.frag"});
        // shaders.registerShader("ident", GL_VERTEX_SHADER,
        //                        {"resources/shaders/ident.vert"});
        // shaders.registerProgram("algosynth", {"ident", "algosynth"});

        // shaders.registerUniform("algosynth", "blend");
    }

    void BlobTraces::update() {
    }

    void BlobTraces::draw() {
        vec_float_t pAPA = getValue<vec_float_t>("/personA/positionA");

        Painter & painter = getPainter();

        painter.setColor({1, 0, 0, 1});
        painter.rect({0.25, 0.25}, {.5, .5});

        auto widthF = funcConst(30);
        auto distF  = funcSin(0.1, 0.05, 0.1, 0);
        auto colorF = funcConst(glm::vec4(0, 1, 1, 0.6));

        painter.parallels({0.5, 0}, {0.5, 1},
                               20, 20, widthF, distF, colorF,
                               true);

        // glBindFramebuffer(GL_FRAMEBUFFER, idFBO);
        // ...
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // const Context & context = getContext();
        // const ShaderRegistry & registry = context.getShaderRegistry();

        // glUseProgram(registry.getProgram("textured"));
        // glUniform1ui(registry.getUniform("textured", "useAlpha"), false);

        // glm::mat4 mvp =
        //     context.getProjection2D() *
        //     context.getToViewportTransform();

        // GLint locMVP = registry.getUniform("textured", "mvp");
        // glUniformMatrix4fv(locMVP, 1, GLboolean(false),
        //                    glm::value_ptr(mvp));

        // texture->draw();
    }
}
