#include <exception>
#include <cstring>

#include <Utility/Logging.hpp>
#include <Graphics/Texture.hpp>

#include "Image.hpp"

namespace etudes {

    using logging::LogLevel;

    void Image::load(std::string filename) {
        log(LogLevel::debug, "Image: loading " + filename);
        if(!image.load(filename.c_str())) {
            std::string message = "failed to load image: " + filename;
            throw(std::runtime_error(message));
        }
        image.convertTo24Bits();
    }

    int Image::getWidth() {
        return image.getWidth();
    }

    int Image::getScanWidth() {
        return image.getScanWidth();
    }

    int Image::getHeight() {
        return image.getHeight();
    }

    int Image::getBitsPerPixel() {
        return image.getBitsPerPixel();
    }

    size_t Image::getByteSize() {
        return image.getImageSize();
    }

    unsigned char *Image::getData() {
        return image.accessPixels();
    }

    void Image::setSourceArea(const Rect &area) {
        sourceArea = area;
    }

    void Image::uploadToTexture(Texture *texture) {
        unsigned char *texData = texture->mapData();

        int texWidth = texture->getWidth();
        int texHeight = texture->getHeight();

        unsigned char *imgData = getData();
        int imgWidth = getWidth();
        int imgScanWidth = getScanWidth();
        int imgHeight = getHeight();

        int rowImage[texHeight];
        int colImage[texWidth];

        float texWidthInv = 1.f / float(texWidth);
        float texHeightInv = 1.f / float(texHeight);

        for(int row = 0 ; row < texHeight ; ++row) {
            rowImage[row] =
                imgHeight * (
                    sourceArea.getPosY() +
                    float(row) * texHeightInv *
                    sourceArea.getHeight()
                    );

        }
        for(int col = 0 ; col < texWidth ; ++col) {
            colImage[col] =
                imgWidth * (
                    sourceArea.getPosX() +
                    float(col) * texWidthInv *
                    sourceArea.getWidth()
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

        texture->unmapData();
    }

}
