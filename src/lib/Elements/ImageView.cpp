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
        int texWidth = 1024;
        int texHeight = 1024;

        int bpp = loader->getBitsPerPixel();
        log(LogLevel::debug, "image size: " +
            std::to_string(imgWidth) + " x " + std::to_string(imgHeight));
        log(LogLevel::debug, "image bpp: " + std::to_string(bpp));
        log(LogLevel::debug, "texture size: " +
            std::to_string(texWidth) + " x " + std::to_string(texHeight));

        texture = std::make_unique<Texture>(texWidth, texHeight, false);
    }

    void ImageView::uploadTextureData() {
        unsigned char *texData = texture->mapData();

        int texWidth = texture->getWidth();
        int texHeight = texture->getHeight();

        unsigned char *imgData = loader->getData();
        int imgWidth = loader->getWidth();
        int imgScanWidth = loader->getScanWidth();
        int imgHeight = loader->getHeight();

        vec2 rangeX = getValue<vec2>("/x-range");
        vec2 rangeY = getValue<vec2>("/y-range");

        int rowImage[texHeight];
        int colImage[texWidth];

        float texWidthInv = 1.f / float(texWidth);
        float texHeightInv = 1.f / float(texHeight);

        for(int row = 0 ; row < texHeight ; ++row) {
            rowImage[row] =
                imgHeight * (
                    rangeY[0] +
                    float(row) * texHeightInv *
                    (rangeY[1] - rangeY[0])
                    );

        }
        for(int col = 0 ; col < texWidth ; ++col) {
            colImage[col] =
                imgWidth * (
                    rangeX[0] +
                    float(col) * texWidthInv *
                    (rangeX[1] - rangeX[0])
                    );
        }

        for(int row = 0 ; row < texHeight ; ++row) {
            for(int col = 0 ; col < texWidth ; ++col) {
                unsigned char *imagePtr =
                    imgData +
                    rowImage[row] * imgScanWidth + colImage[col] * 3;
                unsigned char *texelPtr =
                    texData + (row * texWidth + col) * 3;

                memcpy(texelPtr, imagePtr, 3);
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
