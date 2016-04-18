#ifndef ETUDES_TEXTURE
#define ETUDES_TEXTURE

#include <glbinding/gl/gl.h>
#include <glm/matrix.hpp>

#include <Utility/ShaderRegistry.hpp>

namespace etudes {

    class Rect;

    class Texture {
    public:
        Texture(int width, int height, bool mipmaps);

        int getWidth();
        int getHeight();
        unsigned char *mapData();

        void setHueShift(float hueShift);

        void draw(const glm::mat4 &mvp);

    private:
        void createTextureStorage();
        void createGeometry();

        void uploadData();

        int width, height;
        bool mipmaps;

        float hueShift;

        ShaderRegistry registry;

        gl::GLuint idVertexArray;
        gl::GLuint idTexture;

        gl::GLuint vboTexture;
        gl::GLuint vboVertex;
        gl::GLuint vboUV;

        gl::GLint locMVP;
        gl::GLint locHueShift;

        unsigned char *texture;
    };
}

#endif // ETUDES_TEXTURE
