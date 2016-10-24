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

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/ext.hpp>

#include <Utility/Utility.hpp>

#include <Graphics/Context.hpp>
#include <Graphics/Painter.hpp>
#include <Graphics/Geometry/Transforms.hpp>

#include "Clouds.hpp"

namespace {
    const int numLayers = 3;
}

namespace etudes {

    using namespace gl;

    using glm::vec2;
    using glm::vec4;

    using util::checkGLError;

    void Clouds::registerInputs()
    {
       registerInput("scale", vec_float_t{1.0f});

        for(int layer = 0 ; layer < numLayers ; ++layer)
            registerLayerInputs(layer);
    }

    void Clouds::init()
    {
        ShaderRegistry & shaders = getShaderRegistry();

        shaders.registerShader("clouds", GL_FRAGMENT_SHADER,
                               {"resources/shaders/elements/clouds.frag"});
        shaders.registerProgram("clouds", {"mvp-uv", "clouds"});

        shaders.registerUniform("clouds", "mvp");
        shaders.registerUniform("clouds", "scale");
        shaders.registerUniform("clouds", "layers");

        checkGLError("Clouds::init");
    }

    void Clouds::update()
    {

        checkGLError("Clouds::update");
    }

    void Clouds::draw()
    {
        ShaderRegistry & shaders = getShaderRegistry();
        glUseProgram(shaders.getProgram("clouds"));

        glUniform1f(shaders.getUniform("clouds", "scale"),
                    getValue<float>("scale"));

        for(int layer = 0 ; layer < numLayers ; ++layer)
            setLayerUniforms(layer);

        Rect area = getContext().getViewport2D();
        glm::mat4 model(
            area.getWidth(),  0, 0, 0,
            0, area.getHeight(), 0, 0,
            0, 0, 1, 0,
            area.getX(), area.getY(), 0, 1);
        model = glm::translate(model, glm::vec3{0.5f, 0.5f, 0.f});
        glm::mat4 mvp = getContext().getProjection2D() * model;

        GLint locMVP = shaders.getUniform("clouds", "mvp");
        glUniformMatrix4fv(locMVP, 1, GLboolean(false),
                           glm::value_ptr(mvp));

        quad.draw();
    }

    void Clouds::registerLayerInputs(int layer)
    {
        char input[64];

        sprintf(input, "layer%d/freq", layer);
        registerInput(input, vec_float_t{1.0f});
        sprintf(input, "layer%d/amplitude", layer);
        registerInput(input, vec_float_t{1.0f});
        sprintf(input, "layer%d/origin", layer);
        registerInput(input, vec_float_t{0.0f, 0.0f});
        sprintf(input, "layer%d/color", layer);
        registerInput(input, vec_float_t{1.0f, 1.0f, 1.0f, 1.0f});
    }

    void Clouds::setLayerUniforms(int layer)
    {
        ShaderRegistry & shaders = getShaderRegistry();

        GLint location;

        char uniform[64];
        char input[64];

        sprintf(uniform, "layers[%d].freq", layer);
        sprintf(input,   "layer%d/freq", layer);
        location = glGetUniformLocation(shaders.getProgram("clouds"), uniform);
        glUniform1f(location, getValue<float>(input));

        sprintf(uniform, "layers[%d].amplitude", layer);
        sprintf(input,   "layer%d/amplitude", layer);
        location = glGetUniformLocation(shaders.getProgram("clouds"), uniform);
        glUniform1f(location, getValue<float>(input));

        sprintf(uniform, "layers[%d].origin", layer);
        sprintf(input,   "layer%d/origin", layer);
        vec2 origin = getValue<vec2>(input);
        location = glGetUniformLocation(shaders.getProgram("clouds"), uniform);
        glUniform2f(location, origin[0], origin[1]);

        sprintf(uniform, "layers[%d].color", layer);
        sprintf(input,   "layer%d/color", layer);
        vec4 color = getValue<vec4>(input);
        location = glGetUniformLocation(shaders.getProgram("clouds"), uniform);
        glUniform4f(location, color[0], color[1], color[2], color[3]);
    }
}
