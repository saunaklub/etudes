#include <cmath>
#include <cstring>

#include <Utility/Logging.hpp>

#include "TextureTiled.hpp"

using namespace gl;

namespace etudes {
    using logging::LogLevel;

    TextureTiled::TextureTiled(int width, int height,
                               int tileWidth, int tileHeight,
                               bool mipmaps) :
        width(width),
        height(height),
        tileWidth(tileWidth),
        tileHeight(tileHeight),
        mipmaps(mipmaps) {

        createTextureStorage();
        createGeometry();
    }

    void TextureTiled::createTextureStorage() {
        numTilesX = width / tileWidth;
        if(width % tileWidth)
            numTilesX++;

        numTilesY = height / tileHeight;
        if(height % tileHeight)
            numTilesY++;

        log(LogLevel::debug, "TextureTiled: creating " +
            std::to_string(numTilesX) + "x" + std::to_string(numTilesY) +
            " tiles");

        int numTilesMin = std::min(numTilesX, numTilesY);
        int mipLevelCount = 1;
        if(mipmaps) mipLevelCount = std::log(numTilesMin)/std::log(2);

        glGenTextures(1, &idTexture);
        glBindTexture(GL_TEXTURE_2D_ARRAY, idTexture);

        glTexParameteri(GL_TEXTURE_2D_ARRAY,
                        GL_TEXTURE_MIN_FILTER, GLint(GL_LINEAR));
        glTexParameteri(GL_TEXTURE_2D_ARRAY,
                        GL_TEXTURE_MAG_FILTER, GLint(GL_LINEAR));
        glTexParameteri(GL_TEXTURE_2D_ARRAY,
                        GL_TEXTURE_WRAP_S, GLint(GL_REPEAT));
        glTexParameteri(GL_TEXTURE_2D_ARRAY,
                        GL_TEXTURE_WRAP_T, GLint(GL_REPEAT));

        glTexStorage3D(GL_TEXTURE_2D_ARRAY,
                       mipLevelCount, GL_RGB8UI,
                       tileWidth, tileHeight, numTilesX*numTilesY);
    }

    void TextureTiled::createGeometry() {
        glGenVertexArrays(1, &idVertexArray);
        glBindVertexArray(idVertexArray);

        std::array<float, 12> aCoords = {
            -1.0f,  1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
             1.0f,  1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
        };

        glGenBuffers(1, &idVertex);
        glBindBuffer(GL_ARRAY_BUFFER, idVertex);
        glBufferData(GL_ARRAY_BUFFER,
                     aCoords.size()*sizeof(GLfloat),
                     aCoords.data(),
                     GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        std::array<float, 12> aUV = {
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
        };

        glGenBuffers(1, &idUV);
        glBindBuffer(GL_ARRAY_BUFFER, idUV);
        glBufferData(GL_ARRAY_BUFFER,
                     aUV.size()*sizeof(GLfloat),
                     aUV.data(),
                     GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    void TextureTiled::uploadData(unsigned char *data) {
        size_t size = numTilesY*numTilesY*3*tileHeight*tileHeight;
        char *test = new char[size];
        memset(test, 100, size);

        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0,
                        tileWidth, tileHeight, numTilesX*numTilesY,
                        GL_RGB, GL_UNSIGNED_BYTE, test);

        delete [] test;

        if(mipmaps)
            glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    }

    void TextureTiled::render() {
        glBindVertexArray(idVertexArray);

        glBindTexture(GL_TEXTURE_2D_ARRAY, idTexture);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

}
