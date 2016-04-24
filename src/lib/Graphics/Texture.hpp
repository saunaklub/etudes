#ifndef ETUDES_TEXTURE
#define ETUDES_TEXTURE

#include <glbinding/gl/gl.h>
#include <glm/matrix.hpp>

#include <Graphics/ShaderRegistry.hpp>

namespace etudes {

    class Rect;

    class Texture {
    public:
        Texture(int width, int height, bool mipmaps);

        int getWidth();
        int getHeight();
        unsigned char *mapData();

        void draw();

    private:
        void createTextureStorage();
        void createGeometry();

        void uploadData();

        int width, height;
        bool mipmaps;

        gl::GLuint idVertexArray;
        gl::GLuint idTexture;

        gl::GLuint vboTexture;
        gl::GLuint vboVertex;
        gl::GLuint vboUV;

        unsigned char *texture;
    };
}

#endif // ETUDES_TEXTURE
