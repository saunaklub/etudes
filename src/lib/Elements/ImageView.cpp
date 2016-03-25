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

        int imgWidth = loader->getWidth();
        int imgHeight = loader->getHeight();
        int texWidth = 2048;
        int texHeight = 2048;

        int bpp = loader->getBitsPerPixel();
        log(LogLevel::debug, "image size: " +
            std::to_string(imgWidth) + " x " + std::to_string(imgHeight));
        log(LogLevel::debug, "image bpp: " + std::to_string(bpp));
        log(LogLevel::debug, "texture size: " +
            std::to_string(texWidth) + " x " + std::to_string(texHeight));

        texture = std::make_unique<Texture>(texWidth, texHeight, false);
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
            int rowImage =
                imgHeight * (
                    rangeY[0] +
                    float(row) / float(texHeight) *
                    (rangeY[1] - rangeY[0])
                    );

            for(int col = 0 ; col < texWidth ; ++col) {
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

    void ImageView::draw(const Painter &painter) {
        uploadTextureData();

        float hueShift = getValue<float>("/hue-shift");
        texture->setHueShift(hueShift);

        texture->render();
    }

}
