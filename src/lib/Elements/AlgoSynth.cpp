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
        registerInput("program-values", vec_int_t{0});
        registerInput("program-colors", vec_int_t{0});
        registerInput("rate", vec_float_t{1.f});
        registerInput("cutoff", vec_float_t{1.f});
        registerInput("bitshift1", vec_int_t{0});
        registerInput("bitshift2", vec_int_t{0});
        registerInput("bitmask", vec_int_t{0});
        registerInput("blend", vec_float_t{1});
    }

    void AlgoSynth::init() {
        width = 256;
        height = 192;
        // width = 128;
        // height = 96;

        quad = std::make_unique<Quad>();
        texture = std::make_unique<Texture>(width, height);

        // glGenFramebuffers(1, &idFBO);
        // glBindFramebuffer(GL_FRAMEBUFFER, idFBO);
        // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
        //                        GL_TEXTURE_2D, texture->getId(), 0);
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ShaderRegistry & shaders = getShaderRegistry();

        shaders.registerShader("algosynth", GL_FRAGMENT_SHADER,
                               {"resources/shaders/elements/algosynth.frag"});
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
        ShaderRegistry & shaders = getShaderRegistry();

        glUseProgram(shaders.getProgram("algosynth"));

        int bitshift1 = getValue<int>("bitshift1");
        int bitshift2 = getValue<int>("bitshift2");
        int bitmask = getValue<int>("bitmask");

        float cutoff = getValue<float>("cutoff");
        float rate = getValue<float>("rate");
        float seconds = util::seconds();

        int programValues = getValue<int>("program-values");
        int programColors = getValue<int>("program-colors");

        glUniform1i(shaders.getUniform("algosynth", "programValues"),
                    programValues);
        glUniform1i(shaders.getUniform("algosynth", "programColors"),
                    programColors);

        glUniform1f(shaders.getUniform("algosynth", "seconds"), seconds);
        glUniform1f(shaders.getUniform("algosynth", "rate"), rate);
        glUniform1f(shaders.getUniform("algosynth", "cutoff"), cutoff);

        glUniform1i(shaders.getUniform("algosynth", "bitshift1"), bitshift1);
        glUniform1i(shaders.getUniform("algosynth", "bitshift2"), bitshift2);
        glUniform1i(shaders.getUniform("algosynth", "bitmask"), bitmask);

        glUniform1f(shaders.getUniform("algosynth", "blend"),
                    getValue<float>("blend"));

        // glBindFramebuffer(GL_FRAMEBUFFER, idFBO);
        // quad->draw();
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);

        int val1;
        int val2;
        int r;
        int g;
        int b;

        Array2D<unsigned char> texData(texture->mapData(),
                                       texture->getWidth()*4);
        for(int row = 0 ; row < texture->getHeight() ; ++row) {
            for(int col = 0 ; col < texture->getWidth() ; ++col) {
                // int value = (col<<1) ^ (row+1+int(seconds()*100));
                // int value2 = (row<<1) ^ (row+1+int(seconds()*120));
                // texData[row][3*col+0] = value2;
                // texData[row][3*col+1] = value;
                // texData[row][3*col+2] = ~value2;

                // int value = (col<<1) ^ (row+1+int(seconds()*10));
                // int value2 = (row<<1) ^ (row+1+int(seconds()*12));
                // texData[row][3*col+0] = value2;
                // texData[row][3*col+1] = value * value2;
                // texData[row][3*col+2] = ~value2;
                int t = row * texture->getWidth() * col;

                t = int(t * rate) & bitmask;

                // int a =
                //     (row >> bitshift2) & (col >> bitshift1) *
                //     int(seconds()*rate*(row^col));

                switch(programValues) {
                case 0: {
                    val1 = (row >> bitshift2) & (col >> bitshift1) *
                        int(seconds/1000.0f*rate*(row^col));
                    val2 = ~val1;
                    break;
                }

                case 1: {
                    val1 = (t << bitshift2) & (col << bitshift1) *
                        int(seconds/1000.0f*rate*(row^t));
                    break;
                }

                case 2: {
                    val1 =
                        (t >>  bitshift1) &
                        (t >>  bitshift2) | int(seconds*row);
                    val2 = (t >> bitshift2) | (t | int(seconds*row));
                    break;
                }

                case 3: {
                    val1 =
                        (t >>  bitshift1) &
                        (t >>  bitshift2) | int(seconds*row);
                    val2 = (t >> bitshift2) | (t & int(seconds*col));
                    break;
                }

                case 4: {
                    int i = 10;
                    val1 =
                        (t >>  bitshift1) +
                        (t >>  bitshift2) | int(seconds*col / i);
                    val2 = (t >> bitshift1) | (t & int(seconds*row / i));
                    break;
                }

                default:
                    val1 =
                        int(rate * t) >>  bitshift1 &
                        int(rate * t / 6) >>  bitshift2 | int(seconds*col);
                    val2 = int(rate * t / 7) >> bitshift1 | (t & int(seconds*row));
                    break;
                }
                // val1 =
                //     (t >>  bitshift1) &
                //     (t >>  bitshift2) | int(seconds()*row);
                // val2 = (t >> bitshift2) | (t & int(seconds()*col));
                switch(programColors) {
                case 0: {
                    r = int(val2 * (cutoff) * (1-float(col)/width));
                    g = int(val1 * (cutoff) * (float(col)/width));
                    b = int(val2 * (1-cutoff));
                    break;
                }

                case 1: {
                    r = int(val2 * (cutoff));
                    g = int(val1 * (1-cutoff));
                    b = 0;
                    break;
                }

                default: {
                    r = int(val1 * cutoff);
                    g = int(~val2 * cutoff) & bitmask;
                    b = 0;
                    break;
                }
                }

                // r = val2;
                // g = int(val1 * (cutoff));
                // b = ~val2 * (1-cutoff);

                texData[row][4*col+0] = r;
                texData[row][4*col+1] = g;
                texData[row][4*col+2] = b;
                texData[row][4*col+3] = 255;
            }
        }
        texture->unmapData();
        texture->uploadData();
    }

    void AlgoSynth::draw() {
        const Context & context = getContext();
        ShaderRegistry & shaders = getShaderRegistry();

        glUseProgram(shaders.getProgram("textured"));
        glUniform1ui(shaders.getUniform("textured", "useAlpha"), false);

        glm::mat4 mvp =
            context.getProjection2D() *
            context.getToViewportTransform();

        GLint locMVP = shaders.getUniform("textured", "mvp");
        glUniformMatrix4fv(locMVP, 1, GLboolean(false),
                           glm::value_ptr(mvp));

        texture->draw();
    }
}
