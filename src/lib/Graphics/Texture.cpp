#include <cmath>
#include <cstring>

#include <Utility/Logging.hpp>

#include "Texture.hpp"

using namespace gl;

namespace etudes {
    using logging::LogLevel;

    Texture::Texture(int width, int height, bool mipmaps) :
        width(width),
        height(height),
        mipmaps(mipmaps) {

        registry.registerShader("ident-uv", GL_VERTEX_SHADER,
                                 {"resources/shaders/ident-uv.vert"});
        registry.registerShader("textured", GL_FRAGMENT_SHADER,
                                 {"resources/shaders/textured-hueshift.frag"});
        registry.registerProgram("textured", {"ident-uv", "textured"});

        locHueShift = glGetUniformLocation(registry.getProgram("textured"),
                                           "hueShift");

        createTextureStorage();
        createGeometry();
    }

    void Texture::createTextureStorage() {
        glGenTextures(1, &idTexture);
        glBindTexture(GL_TEXTURE_2D, idTexture);

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER, GLint(GL_LINEAR));
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MAG_FILTER, GLint(GL_LINEAR));
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_S, GLint(GL_REPEAT));
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_T, GLint(GL_REPEAT));

        // @todo calc number of mipmap levels depending on extents
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);

        texture = new unsigned char[width*height*4];
    }

    void Texture::createGeometry() {
        glGenVertexArrays(1, &idVertexArray);
        glBindVertexArray(idVertexArray);

        std::array<float, 12> aCoords = {
            -1.0f,  1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
        };

        glGenBuffers(1, &vboVertex);
        glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
        glBufferData(GL_ARRAY_BUFFER,
                     aCoords.size()*sizeof(GLfloat),
                     aCoords.data(),
                     GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        std::array<float, 12> aUV = {
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
        };

        glGenBuffers(1, &vboUV);
        glBindBuffer(GL_ARRAY_BUFFER, vboUV);
        glBufferData(GL_ARRAY_BUFFER,
                     aUV.size()*sizeof(GLfloat),
                     aUV.data(),
                     GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    int Texture::getWidth() {
        return width;
    }

    int Texture::getHeight() {
        return height;
    }

    unsigned char *Texture::getData() {
        return texture;
    }

    void Texture::setHueShift(float hueShift) {
        this->hueShift = hueShift;
    }

    void Texture::uploadData() {

        // @todo: mark as dirty from client code
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height,
                        GL_BGRA, GL_UNSIGNED_BYTE, texture);
    }

    void Texture::render() {
        glUseProgram(registry.getProgram("textured"));
        glBindVertexArray(idVertexArray);

        glBindTexture(GL_TEXTURE_2D, idTexture);

        uploadData();

        glUniform1f(locHueShift, hueShift);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glBindVertexArray(0);
        glUseProgram(0);
    }

}
