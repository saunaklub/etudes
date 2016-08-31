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

#include <Utility/Utility.hpp>

#include "Rect.hpp"

namespace etudes {

    Rect::Rect() :
        Rect(0, 0, 0, 0) {
    }

    Rect::Rect(float x, float y, float width, float height) :
        x(x),
        y(y),
        width(width),
        height(height) {
    }

    float Rect::getX() const {
        return x;
    }

    float Rect::getY() const {
        return y;
    }

    float Rect::getWidth() const {
        return width;
    }

    float Rect::getHeight() const {
        return height;
    }

    float Rect::getDiagonal() const {
        return std::sqrt(width * width + height * height);
    }

    void Rect::setX(float x) {
        this->x = x;
    }

    void Rect::setY(float y) {
        this->y = y;
    }

    void Rect::setWidth(float width) {
        this->width = width;
    }

    void Rect::setHeight(float height) {
        this->height = height;
    }

    Rect Rect::maximizedTo(const Rect &target, Scaling scaling) const {
        float aspect = getWidth() / getHeight();
        float aspectTarget = target.getWidth() / target.getHeight();

        Rect result = target;

        switch(scaling) {
        case Scaling::STRETCH:
            break;
        case Scaling::CROP:
            if(aspect >= aspectTarget) {
                result.setWidth(target.getHeight() * aspect);
                result.setX(target.getX() +
                            (target.getWidth() - result.getWidth()) / 2.f);
            }
            else {
                result.setHeight(target.getWidth() / aspect);
                result.setY(target.getY() +
                            (target.getHeight() - result.getHeight()) / 2.f);
            }
            break;
        case Scaling::BORDER:
            if(aspect >= aspectTarget) {
                result.setHeight(target.getWidth() / aspect);
                result.setY(target.getY() +
                            (target.getHeight() - result.getHeight()) / 2.f);
            }
            else {
                result.setWidth(target.getHeight() * aspect);
                result.setX(target.getX() +
                            (target.getWidth() - result.getWidth()) / 2.f);
            }
            break;
        }

        return result;
    }

    std::string Rect::toString() const {
        return "[x: " + std::to_string(x) + ", y: " + std::to_string(y) +
            ", w: " + std::to_string(width) + ", h: " + std::to_string(height) +
            "]";
    }

    std::ostream &operator<<(std::ostream &os,
                             const Rect &t) {
        os << t.toString();
        return os;
    }
}
