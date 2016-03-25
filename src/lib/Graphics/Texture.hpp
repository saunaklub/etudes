#ifndef ETUDES_TEXTURE
#define ETUDES_TEXTURE

#include <glbinding/gl/gl.h>

#include <Utility/ShaderRegistry.hpp>

namespace etudes {
    class Texture {
    public:
        Texture(int width, int height, bool mipmaps);

        int getWidth();
        int getHeight();
        unsigned char *getData();

        void render();

    private:
        void createTextureStorage();
        void createGeometry();
        void loadImage();

        void uploadData();

        int width, height;
        bool mipmaps;

        ShaderRegistry registry;

        gl::GLuint idVertexArray;
        gl::GLuint idTexture;

        gl::GLuint vboVertex;
        gl::GLuint vboUV;

        unsigned char *texture;
    };
}

#endif // ETUDES_TEXTURE