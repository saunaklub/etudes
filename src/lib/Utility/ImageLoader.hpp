#ifndef ETUDES_IMAGELOADER
#define ETUDES_IMAGELOADER

#include <string>

#include <FreeImagePlus.h>

namespace etudes {
    class ImageLoader {
    public:
        void load(std::string filename);

        int getWidth();
        int getHeight();
        int getBitsPerPixel();

        unsigned char *getData();

    private:
        fipImage image;
    };
}

#endif // ETUDES_IMAGELOADER
