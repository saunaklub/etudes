/*

  Études Audiovisuelles - Graphical elements for audiovisual composition.
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

#ifndef ETUDES_TEXTURE
#define ETUDES_TEXTURE

#include <glm/matrix.hpp>

#include <Graphics/Drawable/Quad.hpp>

namespace etudes {

    class Rect;

    class Texture {
    public:
        enum class Filter {
            NEAREST,
            LINEAR,
        };

        Texture(int width, int height);

        int getWidth();
        int getHeight();
        int getChannelCount();
        int getId();

        void setFilter(Filter);
        void setUseAlpha(bool);

        unsigned char *mapData();
        void unmapData();
        void clear();

        void bind();
        void unbind();

        void uploadData();
        void draw();

    private:
        void createTexture();

        Quad quad;

        int width, height;
        Filter filter;
        bool mipmaps;
        bool useAlpha;

        GLuint idTexture;
        GLuint pboTexture;
        unsigned char *texture;
    };
}

#endif // ETUDES_TEXTURE
