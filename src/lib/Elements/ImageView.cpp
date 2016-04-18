#include <glbinding/gl/gl.h>
#include <glm/vec2.hpp>

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

    void ImageView::draw(const Context &context) {
        // replace by range inputs or PanZoom
        image->setSourceArea(Rect(0, 0, 1, 1));
        image->uploadToTexture(texture.get());

        float hueShift = getValue<float>("/hue-shift");
        texture->setHueShift(hueShift);

        Rect area(0, 0, image->getWidth(), image->getHeight());
        area = area.maximizedTo(context.getViewport2D(), Rect::CROP);

        glm::mat4 view(
            area.getWidth(),  0, 0, area.getPosX(),
            0, area.getHeight(), 0, area.getPosY(),
            0, 0, 1, 0,
            0, 0, 0, 1);

        glm::mat4 mvp = view * context.getProjection2D();

        texture->draw(mvp);
    }

}
