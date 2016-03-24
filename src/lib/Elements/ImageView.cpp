#include <cstring>

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
        log(LogLevel::debug, "ImageView: loading image: " + filename);
        loader = std::make_unique<ImageLoader>();
        loader->load(filename);

        // int width = loader->getWidth();
        // int height = loader->getHeight();
        int width = 2048;
        int height = 2048;

        int bpp = loader->getBitsPerPixel();
        log(LogLevel::debug, "image size: " +
            std::to_string(width) + " x " + std::to_string(height));
        log(LogLevel::debug, "image bpp: " + std::to_string(bpp));

       texture = std::make_unique<Texture>(width, height, false);
    }

    void ImageView::draw(const Painter &painter) {
        uploadTextureData();
        texture->render();
    }

    void ImageView::uploadTextureData() {
        unsigned char *texData = texture->getData();
        int texWidth = texture->getWidth();
        int texHeight = texture->getHeight();

        unsigned char *imgData = loader->getData();
        int imgWidth = loader->getWidth();
        int imgHeight = loader->getHeight();

        log(LogLevel::debug, "filling texture of size " +
            std::to_string(texWidth) + " x " +  std::to_string(texHeight));
        for(int row = 0 ; row < texHeight ; ++row) {
            for(int col = 0 ; col < texWidth ; ++col) {
                int idxTexel = row * texWidth + col;

                int rowImage = float(row) / float(texHeight) * imgHeight;
                int colImage = float(col) / float(texWidth) * imgWidth;
                int idxImage = rowImage * imgWidth + colImage;

                memcpy(texData + 4*idxTexel, imgData + 4*idxImage, 4);
            }
        }
    }

}
