#include "PanZoom.hpp"

namespace etudes {

    PanZoom::PanZoom() :
        speed(1.f),
        sourceArea(0, 0, 1, 1) {
    }

    PanZoom::~PanZoom() {
    }

    float PanZoom::getSpeed() {
        return speed;
    }

    void PanZoom::setSpeed(float speed) {
        this->speed = speed;
    }

    Rect PanZoom::getSourceArea() {
        return sourceArea;
    }

    void PanZoom::setSourceArea(const Rect &area) {
        sourceArea = area;
    }

}
