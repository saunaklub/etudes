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

#include <exception>
#include <cstring>

#include <Utility/Logging.hpp>
#include <Graphics/Texture.hpp>

#include "Image.hpp"

namespace etudes {

    using logging::LogLevel;

    void Image::load(std::string filename) {
        log(LogLevel::debug, "Image: loading " + filename);
        if(!image.load(filename.c_str())) {
            std::string message = "failed to load image: " + filename;
            throw(std::runtime_error(message));
        }
        image.convertTo32Bits();
    }

    int Image::getWidth() {
        return image.getWidth();
    }

    int Image::getScanWidth() {
        return image.getScanWidth();
    }

    int Image::getHeight() {
        return image.getHeight();
    }

    int Image::getBitsPerPixel() {
        return image.getBitsPerPixel();
    }

    size_t Image::getByteSize() {
        return image.getImageSize();
    }

    unsigned char *Image::getData() {
        return image.accessPixels();
    }

    void Image::setSourceArea(const Rect &area) {
        sourceArea = area;
    }

    void Image::uploadToTexture(Texture *texture) {
        unsigned char *texData = texture->mapData();

        const int texWidth = texture->getWidth();
        const int texHeight = texture->getHeight();

        unsigned char *imgData = getData();
        const int imgWidth = getWidth();
        const int imgScanWidth = getScanWidth();
        const int imgHeight = getHeight();

        int rowImage[texHeight];
        int colImage[texWidth];

        const float texWidthInv = 1.f / float(texWidth);
        const float texHeightInv = 1.f / float(texHeight);

        for(int row = 0 ; row < texHeight ; ++row) {
            rowImage[row] =
                imgHeight * (
                    sourceArea.getPosY() +
                    float(row) * texHeightInv *
                    sourceArea.getHeight()
                    );

        }
        for(int col = 0 ; col < texWidth ; ++col) {
            colImage[col] =
                imgWidth * (
                    sourceArea.getPosX() +
                    float(col) * texWidthInv *
                    sourceArea.getWidth()
                    );
        }

        for(int row = 0 ; row < texHeight ; ++row) {
            for(int col = 0 ; col < texWidth ; ++col) {
                unsigned char *imagePtr =
                    imgData +
                    rowImage[row] * imgScanWidth + colImage[col] * 4;
                unsigned char *texelPtr =
                    texData + (row * texWidth + col) * 4;

               memcpy(texelPtr, imagePtr, 4);
            }
        }

        texture->unmapData();
    }

}
