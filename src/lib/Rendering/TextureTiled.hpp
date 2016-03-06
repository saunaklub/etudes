#ifndef ETUDES_TEXTURETILED
#define ETUDES_TEXTURETILED

#include <glbinding/gl/gl.h>

namespace etudes {
    class TextureTiled {
    public:
        TextureTiled(int width, int height,
                     int tileWidth, int tileHeight,
                     bool mipmaps);

        void uploadData(unsigned char *data,
                        int width, int height);

        void render();

    private:
        void createTextureStorage();
        void createGeometry();

        int width, height;
        int tileWidth, tileHeight;
        int numTilesX, numTilesY;

        bool mipmaps;

        gl::GLuint idVertexArray;
        gl::GLuint idVertex;
        gl::GLuint idUV;

        gl::GLuint idTexture;
    };
}

#endif // ETUDES_TEXTURETILED
