#ifndef ETUDES_IMAGE
#define ETUDES_IMAGE

#include <memory>

#include <FreeImagePlus.h>

#include <Graphics/Geometry/Rect.hpp>

namespace etudes {
    class Texture;
    class Image {
    public:
        void load(std::string filename);

        int getWidth();
        int getScanWidth();
        int getHeight();
        int getBitsPerPixel();

        size_t getByteSize();
        unsigned char *getData();

        void setSourceArea(const Rect &area);
        void uploadToTexture(Texture *texture);

    private:
        fipImage image;
        Rect sourceArea;
    };
}

#endif // ETUDES_IMAGE
