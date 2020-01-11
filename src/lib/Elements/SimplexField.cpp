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
#include <Graphics/Painter.hpp>
#include <Graphics/Geometry/Transforms.hpp>

#include "SimplexField.hpp"

namespace {
    const int texWidth = 256;
    const int texHeight = 256;
}

namespace etudes {

    using util::checkGLError;

    void SimplexField::registerInputs()
    {
       registerInput("scale", vec_float_t{1.0f});
    }

    void SimplexField::init()
    {
        noiseTexture = std::make_unique<Texture>(texWidth, texHeight);
        checkGLError("SimplexField::init");
    }

    void SimplexField::update()
    {
        int channels = noiseTexture->getChannelCount();
        unsigned char * texData = noiseTexture->mapData();

        double seconds = util::seconds();
        float scale =  getValue<float>("scale");

        for (int u = 0 ; u < texWidth ; ++u) {
            for (int v = 0 ; v < texHeight ; ++v) {
                float val = noise.fractal(
                    3,
                    float(u*scale) / texWidth,
                    float(v*scale) / texHeight + seconds);
                val = (val + 1.f) * 0.5f;

                texData[(v * texWidth + u) * channels + 0] = 0;
                texData[(v * texWidth + u) * channels + 1] = 255 * val;
                texData[(v * texWidth + u) * channels + 2] = 255 * val;
                texData[(v * texWidth + u) * channels + 3] = 255;

            }
        }

        noiseTexture->unmapData();
        noiseTexture->uploadData();

        checkGLError("SimplexField::update");
    }

    void SimplexField::draw()
    {
        ShaderRegistry & shaders = getShaderRegistry();

        glUseProgram(shaders.getProgram("textured"));

        Rect area(0, 0, noiseTexture->getWidth(), noiseTexture->getHeight());
        area = area.resizedTo(getContext().getViewport2D(),
                                Rect::Scaling::CROP);

        glm::mat4 model(
            area.getWidth(),  0, 0, 0,
            0, area.getHeight(), 0, 0,
            0, 0, 1, 0,
            area.getX(), area.getY(), 0, 1);
        model = glm::translate(model, glm::vec3{0.5f, 0.5f, 0.f});
        glm::mat4 mvp = getContext().getProjection2D() * model;

        GLint locMVP = shaders.getUniform("textured", "mvp");
        glUniformMatrix4fv(locMVP, 1, GLboolean(false),
                           glm::value_ptr(mvp));

        noiseTexture->draw();
    }
}
