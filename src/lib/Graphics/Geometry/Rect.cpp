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

    float Rect::getPosX() const {
        return x;
    }

    float Rect::getPosY() const {
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

    void Rect::setPosX(float x) {
        this->x = x;
    }

    void Rect::setPosY(float y) {
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
        case STRETCH:
            break;
        case CROP:
            if(aspect >= aspectTarget) {
                result.setWidth(target.getHeight() * aspect);
                result.setPosX(target.getPosX() +
                               (target.getWidth() - result.getWidth()) / 2.f);
            }
            else {
                result.setHeight(target.getWidth() / aspect);
                result.setPosY(target.getPosY() +
                               (target.getHeight() - result.getHeight()) / 2.f);
            }
            break;
        case BORDER:
            if(aspect >= aspectTarget) {
                result.setHeight(target.getWidth() / aspect);
                result.setPosY(target.getPosY() +
                               (target.getHeight() - result.getHeight()) / 2.f);
            }
            else {
                result.setWidth(target.getHeight() * aspect);
                result.setPosX(target.getPosX() +
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
