#ifndef ETUDES_TEXTURE
#define ETUDES_TEXTURE

#include <glbinding/gl/gl.h>
#include <glm/matrix.hpp>

#include <Graphics/ShaderRegistry.hpp>
#include <Graphics/Quad.hpp>

namespace etudes {

    class Rect;

    class Texture {
    public:
        Texture(int width, int height, bool mipmaps);

        int getWidth();
        int getHeight();

        unsigned char *mapData();
        void unmapData();

        void draw();

    private:
        void createTextureStorage();
        void uploadData();

        Quad quad;

        int width, height;
        bool mipmaps;

        gl::GLuint idTexture;
        gl::GLuint vboTexture;
        unsigned char *texture;
    };
}

#endif // ETUDES_TEXTURE
