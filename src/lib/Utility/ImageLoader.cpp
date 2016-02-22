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

    unsigned char *ImageLoader::getData() {
        return image.accessPixels();
    }

}
