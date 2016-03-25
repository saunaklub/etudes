#include <cstring>

#include <glbinding/gl/gl.h>
#include <glm/vec2.hpp>

#include <Utility/Logging.hpp>

#include "ImageView.hpp"

namespace etudes {

    using namespace gl;
    using glm::vec2;
    using logging::LogLevel;

    ImageView::ImageView(std::string filename) :
        filename(filename) {
    }

    void ImageView::registerInputs() {
        registerInput("/x-range", {0, 1});
        registerInput("/y-range", {0, 1});
        registerInput("/hue-shift", {0});
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

        vec2 rangeX = getValue<vec2>("/x-range");
        vec2 rangeY = getValue<vec2>("/y-range");

        for(int row = 0 ; row < texHeight ; ++row) {
            for(int col = 0 ; col < texWidth ; ++col) {
        float hueShift = getValue<float>("/hue-shift");
        texture->setHueShift(hueShift);

                int rowImage =
                    imgHeight * (
                        rangeY[0] +
                        float(row) / float(texHeight) *
                        (rangeY[1] - rangeY[0])
                        );
                int colImage =
                    imgWidth * (
                        rangeX[0] +
                        float(col) / float(texWidth) *
                        (rangeX[1] - rangeX[0])
                        );

                int idxImage = rowImage * imgWidth + colImage;
                int idxTexel = row * texWidth + col;

                memcpy(texData + 4*idxTexel, imgData + 4*idxImage, 4);
            }
        }
    }

}
