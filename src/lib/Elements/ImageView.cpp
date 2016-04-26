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
        registerInput("/x-range", {0, 1});
        registerInput("/y-range", {0, 1});
        registerInput("/hue-shift", {0});
        registerInput("/alpha", {1.f});
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

        texture = std::make_unique<Texture>(texWidth, texHeight, false);
    }

    void ImageView::update() {
        Rect sourceArea;

        if(panZoom) {
            sourceArea = panZoom->getSourceArea();
        }
        else {
            vec2 rangeX = getValue<vec2>("/x-range");
            vec2 rangeY = getValue<vec2>("/y-range");

            sourceArea = Rect(rangeX[0], rangeY[0],
                              rangeX[1] - rangeX[0],
                              rangeY[1] - rangeY[0]);
        }

        image->setSourceArea(sourceArea);
        image->uploadToTexture(texture.get());
    }

    void ImageView::draw(const Context &context,
                         const Painter &painter) {
        const ShaderRegistry &registry = context.getShaderRegistry();

        glUseProgram(registry.getProgram("textured"));

        float hueShift = getValue<float>("/hue-shift");
        float alpha = getValue<float>("/alpha");
        glUniform1f(registry.getUniform("textured", "hueShift"), hueShift);
        glUniform1f(registry.getUniform("textured", "alpha"), alpha);

        Rect area(0, 0, image->getWidth(), image->getHeight());
        area = area.maximizedTo(context.getViewport2D(), Rect::CROP);

        glm::mat4 model(
            area.getWidth(),  0, 0, 0,
            0, area.getHeight(), 0, 0,
            0, 0, 1, 0,
            area.getPosX(), area.getPosY(), 0, 1);
        model = glm::translate(model, glm::vec3{0.5f, 0.5f, 0.f});
        glm::mat4 mvp = context.getProjection2D() * model;

        GLint locMVP =
            context.getShaderRegistry().getUniform("textured", "mvp");
        glUniformMatrix4fv(locMVP, 1, GLboolean(false),
                           glm::value_ptr(mvp));

        texture->draw();
    }

}
