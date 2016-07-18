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
#include <Utility/Array2D.hpp>

#include <Graphics/Context.hpp>
#include <Graphics/Painter.hpp>

#include "AlgoSynth.hpp"

namespace etudes {

    using namespace gl;
    using logging::LogLevel;

    AlgoSynth::AlgoSynth() {
    }

    void AlgoSynth::registerInputs() {
        registerInput("/program-values", vec_int_t{0});
        registerInput("/program-colors", vec_int_t{0});
        registerInput("/rate", vec_float_t{1.f});
        registerInput("/cutoff", vec_float_t{1.f});
        registerInput("/bitshift1", vec_int_t{0});
        registerInput("/bitshift2", vec_int_t{0});
        registerInput("/bitmask", vec_int_t{0});
        registerInput("/blend", vec_float_t{1});
    }

    void AlgoSynth::init() {
        // width = 256;
        // height = 192;
        width = 128;
        height = 96;

        quad = std::make_unique<Quad>();
        texture = std::make_unique<Texture>(width, height);

        glGenFramebuffers(1, &idFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, idFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, texture->getId(), 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        shaders.registerShader("algosynth", GL_FRAGMENT_SHADER,
                               {"resources/shaders/algosynth.frag"});
        shaders.registerShader("ident", GL_VERTEX_SHADER,
                               {"resources/shaders/ident.vert"});
        shaders.registerProgram("algosynth", {"ident", "algosynth"});

        shaders.registerUniform("algosynth", "programValues");
        shaders.registerUniform("algosynth", "programColors");

        shaders.registerUniform("algosynth", "seconds");
        shaders.registerUniform("algosynth", "rate");
        shaders.registerUniform("algosynth", "cutoff");
        shaders.registerUniform("algosynth", "bitshift1");
        shaders.registerUniform("algosynth", "bitshift2");
        shaders.registerUniform("algosynth", "bitmask");

        shaders.registerUniform("algosynth", "blend");
    }

    void AlgoSynth::update() {
        renderTexture();
    }

    void AlgoSynth::renderTexture() {
        glUseProgram(shaders.getProgram("algosynth"));

        glUniform1ui(shaders.getUniform("algosynth", "programValues"),
                    getValue<int>("/program-values"));
        glUniform1ui(shaders.getUniform("algosynth", "programColors"),
                    getValue<int>("/program-colors"));

        glUniform1f(shaders.getUniform("algosynth", "seconds"), seconds());
        glUniform1f(shaders.getUniform("algosynth", "rate"),
                    getValue<float>("/rate"));
        glUniform1f(shaders.getUniform("algosynth", "cutoff"),
                    getValue<float>("/cutoff"));

        glUniform1ui(shaders.getUniform("algosynth", "bitshift1"),
                    getValue<int>("/bitshift1"));
        glUniform1ui(shaders.getUniform("algosynth", "bitshift2"),
                    getValue<int>("/bitshift2"));
        glUniform1ui(shaders.getUniform("algosynth", "bitmask"),
                    getValue<int>("/bitmask"));

        glUniform1f(shaders.getUniform("algosynth", "blend"),
                    getValue<float>("/blend"));

        glBindFramebuffer(GL_FRAMEBUFFER, idFBO);
        quad->draw();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void AlgoSynth::draw(const Context &context,
                         const Painter &painter) {

        const ShaderRegistry &registry = context.getShaderRegistry();

        glUseProgram(registry.getProgram("textured"));
        glUniform1ui(registry.getUniform("textured", "useAlpha"), false);

        glm::mat4 mvp =
            context.getProjection2D() *
            context.getToViewportTransform();

        GLint locMVP = registry.getUniform("textured", "mvp");
        glUniformMatrix4fv(locMVP, 1, GLboolean(false),
                           glm::value_ptr(mvp));

        texture->draw();
    }
}
