/*

  Études Audiovisuels - Graphical elements for audiovisual composition.
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
#include <glm/ext.hpp>

#include <Utility/Logging.hpp>

#include <Graphics/Geometry/Rect.hpp>

#include "ImageView.hpp"

namespace etudes {

    using namespace gl;
    using glm::vec2;
    using logging::LogLevel;

    ImageView::ImageView(std::string filename,
                         std::unique_ptr<PanZoom> panZoom) :
        filename(filename),
        panZoom(std::move(panZoom)) {
    }

    void ImageView::registerInputs() {
        registerInput("x-range", vec_float_t{0, 1});
        registerInput("y-range", vec_float_t{0, 1});
        registerInput("shift-hue", vec_float_t{0});
        registerInput("shift-saturation", vec_float_t{0});
        registerInput("shift-value", vec_float_t{0});
        registerInput("alpha", vec_float_t{1.f});
    }

    void ImageView::init() {
        image = std::make_unique<Image>();

        image->load(filename);

        int imgWidth = image->getWidth();
        int imgHeight = image->getHeight();

        int texWidth = 1024;
        int texHeight = 1024;

        int bpp = image->getBitsPerPixel();
        log(LogLevel::debug, "image size: " +
            std::to_string(imgWidth) + " x " + std::to_string(imgHeight));
        log(LogLevel::debug, "image bpp: " + std::to_string(bpp));
        log(LogLevel::debug, "texture size: " +
            std::to_string(texWidth) + " x " + std::to_string(texHeight));

        texture = std::make_unique<Texture>(texWidth, texHeight);
        texture->setFilter(Texture::Filter::LINEAR);
    }

    void ImageView::update() {
        Rect sourceArea;

        if(panZoom) {
            sourceArea = panZoom->getSourceArea();
        }
        else {
            vec2 rangeX = getValue<vec2>("x-range");
            vec2 rangeY = getValue<vec2>("y-range");

            sourceArea = Rect(rangeX[0], rangeY[0],
                              rangeX[1] - rangeX[0],
                              rangeY[1] - rangeY[0]);
        }

        image->setSourceArea(sourceArea);
        image->uploadToTexture(texture.get());
    }

    void ImageView::draw() {
        ShaderRegistry & shaders = getShaderRegistry();

        glUseProgram(shaders.getProgram("textured"));

        float shiftHue = getValue<float>("shift-hue");
        float shiftSaturation = getValue<float>("shift-saturation");
        float shiftValue = getValue<float>("shift-value");
        float alpha = getValue<float>("alpha");
        glUniform1f(
            shaders.getUniform("textured", "shiftHue"), shiftHue);
        glUniform1f(
            shaders.getUniform("textured", "shiftSaturation"), shiftSaturation);
        glUniform1f(
            shaders.getUniform("textured", "shiftValue"), shiftValue);
        glUniform1f(shaders.getUniform("textured", "alpha"), alpha);

        Rect area(0, 0, image->getWidth(), image->getHeight());
        area = area.maximizedTo(getContext().getViewport2D(),
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

        texture->uploadData();
        texture->draw();
    }

}
