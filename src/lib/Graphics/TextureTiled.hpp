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
