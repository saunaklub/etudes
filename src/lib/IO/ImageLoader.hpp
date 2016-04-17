#ifndef ETUDES_IMAGELOADER
#define ETUDES_IMAGELOADER

#include <string>

#include <FreeImagePlus.h>

namespace etudes {
    class ImageLoader {
    public:
        void load(std::string filename);

        int getWidth();
        int getScanWidth();
        int getHeight();
        int getBitsPerPixel();

        size_t getByteSize();
        unsigned char *getData();

    private:
        fipImage image;
    };
}

#endif // ETUDES_IMAGELOADER
