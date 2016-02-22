#include "ImageLoader.hpp"

namespace etudes {

    void ImageLoader::load(std::string filename) {
        image.load(filename.c_str());
    }

    int ImageLoader::getWidth() {
        return image.getWidth();
    }

    int ImageLoader::getHeight() {
        return image.getHeight();
    }

    int ImageLoader::getBitsPerPixel() {
        return image.getBitsPerPixel();
    }

    size_t ImageLoader::getByteSize() {
        return image.getImageSize();
    }

    unsigned char *ImageLoader::getData() {
        return image.accessPixels();
    }

}
