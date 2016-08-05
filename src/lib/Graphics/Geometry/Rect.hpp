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

#ifndef ETUDES_RECT
#define ETUDES_RECT

#include <string>

namespace etudes {
    class Rect {
    public:
        enum class Scaling {
            STRETCH,
            CROP,
            BORDER
        };

        Rect();
        Rect(float x, float y, float width, float height);

        float getPosX() const;
        float getPosY() const;

        float getWidth() const;
        float getHeight() const;
        float getDiagonal() const;

        void setPosX(float x);
        void setPosY(float y);

        void setWidth(float width);
        void setHeight(float height);

        Rect maximizedTo(const Rect &rect, Scaling scaling) const;

        std::string toString() const;

    private:
        float x, y;
        float width, height;
    };

    std::ostream &operator<<(std::ostream &os,
                             const Rect &t);
}

#endif // ETUDES_RECT
