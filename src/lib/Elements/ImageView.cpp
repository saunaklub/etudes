#include <glbinding/gl/gl.h>

#include <Utility/Logging.hpp>

#include "ImageView.hpp"

namespace etudes {

    using namespace gl;
    using logging::LogLevel;

    ImageView::ImageView(std::string filename) :
        filename(filename) {
    }

    void ImageView::registerInputs() {
        registerInput("/hueshift", {0});
    }

    void ImageView::init() {
        ImageLoader loader;

        registry.registerShader("ident", GL_VERTEX_SHADER,
                                 {"resources/shader/ident.vert"});
        registry.registerShader("textured_array", GL_FRAGMENT_SHADER,
                                 {"resources/shader/textured_array.frag"});
        registry.registerProgram("imageview", {"ident", "textured_array"});

        log(LogLevel::debug, "ImageView: loading image: " + filename);
        loader.load(filename);

        int width = loader.getWidth();
        int height = loader.getHeight();
        int bpp = loader.getBitsPerPixel();
        log(LogLevel::debug, "image size: " +
            std::to_string(width) + " x " + std::to_string(height));
        log(LogLevel::debug, "image bpp: " + std::to_string(bpp));

        int tileSize = 2048;
        texture = std::make_unique<TextureTiled>(
            width, height,
            tileSize, tileSize,
            false);

        texture->uploadData(loader.getData(), loader.getByteSize());
    }

    void ImageView::draw() {
        glUseProgram(registry.getProgram("imageview"));
        texture->render();
        glUseProgram(0);
    }

}
