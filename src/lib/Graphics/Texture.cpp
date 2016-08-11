/*

  Études Audiovisuels - Graphical elements for audiovisual composition.
  Copyright (C) 2015-2016 Patric Schmitz

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <cmath>
#include <cstring>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>

#include <Graphics/Geometry/Rect.hpp>

#include "Texture.hpp"

namespace etudes {

    using namespace gl;
    using logging::LogLevel;
    using util::checkGLError;

    Texture::Texture(int width, int height) :
        width(width),
        height(height),
        mipmaps(false),
        useAlpha(true),
        texture(nullptr) {

        createTexture();
        setFilter(Filter::NEAREST);

        clear();
    }

    void Texture::createTexture() {
        glGenTextures(1, &idTexture);
        glBindTexture(GL_TEXTURE_2D, idTexture);

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_S, GLint(GL_REPEAT));
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_T, GLint(GL_REPEAT));

        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
        checkGLError("Texture::createTexture glTexStorage2D");

        glGenBuffers(1, &pboTexture);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboTexture);
        glBufferData(GL_PIXEL_UNPACK_BUFFER,
                     getWidth() * getHeight() * getChannelCount(),
                     nullptr, GL_DYNAMIC_DRAW);
        checkGLError("Texture::createTexture glBufferData");
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }

    void Texture::setFilter(Filter filter) {
        bind();

        switch(filter) {
        case Filter::NEAREST:
            glTexParameteri(GL_TEXTURE_2D,
                            GL_TEXTURE_MIN_FILTER, GLint(GL_NEAREST));
            glTexParameteri(GL_TEXTURE_2D,
                            GL_TEXTURE_MAG_FILTER, GLint(GL_NEAREST));
            break;
        case Filter::LINEAR:
            glTexParameteri(GL_TEXTURE_2D,
                            GL_TEXTURE_MIN_FILTER, GLint(GL_LINEAR));
            glTexParameteri(GL_TEXTURE_2D,
                            GL_TEXTURE_MAG_FILTER, GLint(GL_LINEAR));
            break;
        }

        unbind();
    }

    void Texture::setUseAlpha(bool useAlpha) {
        this->useAlpha = useAlpha;
    }

    int Texture::getWidth() {
        return width;
    }

    int Texture::getHeight() {
        return height;
    }

    int Texture::getChannelCount() {
        return 4;
    }

    int Texture::getId() {
        return idTexture;
    }

    unsigned char *Texture::mapData() {
        if(!texture) {
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboTexture);
            texture = (unsigned char*)(glMapBuffer(GL_PIXEL_UNPACK_BUFFER,
                                                   GL_READ_WRITE));
        }
        checkGLError("Texture::mapData");
        return texture;
    }

    void Texture::unmapData() {
        glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
        checkGLError("Texture::unmapData");
        texture = nullptr;
    }

    void Texture::uploadData() {
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboTexture);

        bind();
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height,
                        GL_BGRA, GL_UNSIGNED_BYTE, 0);
        unbind();

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
        checkGLError("Texture::uploadData");
    }

    void Texture::clear() {
        unsigned char *texData = mapData();
        memset(texData, 0, getWidth() * getHeight() * getChannelCount());
        unmapData();
        uploadData();
    }

    void Texture::bind() {
        glBindTexture(GL_TEXTURE_2D, idTexture);
    }

    void Texture::unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::draw() {
        bind();
        quad.draw();
        unbind();

        checkGLError("Texture::draw quad draw");
    }

}
