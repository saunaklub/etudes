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
        registerInput("/rate", vec_float_t{1.f});
        registerInput("/cutoff", vec_float_t{1.f});
        registerInput("/bitshift1", vec_int_t{0});
        registerInput("/bitshift2", vec_int_t{0});
        registerInput("/bitmask", vec_int_t{0});
    }

    void AlgoSynth::init() {
        width = 256;
        height = 192;

        quad = std::make_unique<Quad>();
        texture = std::make_unique<Texture>(width, height,
                                            Texture::NEAREST, false);

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

        shaders.registerUniform("algosynth", "seconds");
        shaders.registerUniform("algosynth", "rate");
        shaders.registerUniform("algosynth", "cutoff");
        shaders.registerUniform("algosynth", "bitshift1");
        shaders.registerUniform("algosynth", "bitshift2");
        shaders.registerUniform("algosynth", "bitmask");
    }

    void AlgoSynth::update() {
        renderTexture();
    }

    void AlgoSynth::renderTexture() {
        glUseProgram(shaders.getProgram("algosynth"));

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

        glBindFramebuffer(GL_FRAMEBUFFER, idFBO);
        quad->draw();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void AlgoSynth::draw(const Context &context,
                         const Painter &painter) {

        const ShaderRegistry &registry = context.getShaderRegistry();

        glUseProgram(registry.getProgram("textured"));

        Rect area = context.getViewport2D();

        glm::mat4 model(
            area.getWidth() / 2.0f,  0, 0, 0,
            0, area.getHeight() / 2.0f, 0, 0,
            0, 0, 1, 0,
            area.getPosX(), area.getPosY(), 0, 1);
        model = glm::translate(model, glm::vec3{1.0f, 1.0f, 0.f});
        glm::mat4 mvp = context.getProjection2D() * model;

        GLint locMVP = registry.getUniform("textured", "mvp");
        glUniformMatrix4fv(locMVP, 1, GLboolean(false),
                           glm::value_ptr(mvp));

        texture->draw();
    }
}
