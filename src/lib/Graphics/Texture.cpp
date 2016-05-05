/*

  Études Audiovisuel - Graphical elements for audiovisual composition.
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

#include <Utility/Logging.hpp>

#include <Graphics/Geometry/Rect.hpp>

#include "Texture.hpp"

namespace etudes {

    using namespace gl;
    using logging::LogLevel;

    Texture::Texture(int width, int height, bool mipmaps) :
        width(width),
        height(height),
        mipmaps(mipmaps),
        texture(nullptr) {

        createTextureStorage();
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

        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);

        glGenBuffers(1, &vboTexture);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, vboTexture);
        glBufferData(GL_PIXEL_UNPACK_BUFFER,
                     width*height*3,
                     nullptr, GL_DYNAMIC_DRAW);
    }

    int Texture::getWidth() {
        return width;
    }

    int Texture::getHeight() {
        return height;
    }

    unsigned char *Texture::mapData() {
        if(!texture) {
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, vboTexture);
            texture = (unsigned char*)(glMapBuffer(GL_PIXEL_UNPACK_BUFFER,
                                                   GL_WRITE_ONLY));
        }
        return texture;
    }

    void Texture::unmapData() {
        glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
        texture = nullptr;
    }

    void Texture::uploadData() {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height,
                        GL_BGR, GL_UNSIGNED_BYTE, 0);
    }

    void Texture::draw() {
        glBindTexture(GL_TEXTURE_2D, idTexture);
        uploadData();

        quad.draw();
    }

}
