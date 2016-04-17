#include <Utility/Logging.hpp>

#include "ImageLoader.hpp"

namespace etudes {

    using logging::LogLevel;

    void ImageLoader::load(std::string filename) {
        if(!image.load(filename.c_str()))
            log(LogLevel::error, "failed to load image: " + filename);
        image.convertTo24Bits();
    }

    int ImageLoader::getWidth() {
        return image.getWidth();
    }

    int ImageLoader::getScanWidth() {
        return image.getScanWidth();
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
