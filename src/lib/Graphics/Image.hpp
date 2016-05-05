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

#ifndef ETUDES_IMAGE
#define ETUDES_IMAGE

#include <memory>

#include <FreeImagePlus.h>

#include <Graphics/Geometry/Rect.hpp>

namespace etudes {
    class Texture;
    class Image {
    public:
        void load(std::string filename);

        int getWidth();
        int getScanWidth();
        int getHeight();
        int getBitsPerPixel();

        size_t getByteSize();
        unsigned char *getData();

        void setSourceArea(const Rect &area);
        void uploadToTexture(Texture *texture);

    private:
        fipImage image;
        Rect sourceArea;
    };
}

#endif // ETUDES_IMAGE
