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

#ifndef ETUDES_IMAGEVIEW
#define ETUDES_IMAGEVIEW

#include <memory>

#include <glow/fwd.hh>

#include <Receivers/Element.hpp>

#include <Graphics/Image.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/PanZoom.hpp>

namespace etudes {

    class ImageView : public Element {
    public:
        ImageView(std::string filename,
                  std::unique_ptr<PanZoom> panZoom);

        void registerInputs() override;

        void init() override;
        void update() override;
        void draw() override;

    private:
        std::string filename;

        std::unique_ptr<Image> image;
        std::unique_ptr<PanZoom> panZoom;

        glow::SharedProgram program;
        glow::SharedTexture2D texture;
    };
}

#endif // ETUDES_IMAGEVIEW
