#include "PanZoom.hpp"

namespace etudes {

    PanZoom::PanZoom() :
        zoom(1.f),
        aspectRatio(1.f) {
    }

    float PanZoom::getZoom() {
        return zoom;
    }

    void PanZoom::setZoom(float zoom) {
        this->zoom = zoom;
    }

    float PanZoom::getAspectRatio() {
        return aspectRatio;
    }

    void PanZoom::setAspectRatio(float aspectRatio) {
        this->aspectRatio = aspectRatio;
    }

    float PanZoom::getSpeed() {
        return speed;
    }

    void PanZoom::setSpeed(float speed) {
        this->speed = speed;
    }

    glm::vec2 PanZoom::getCenter() {
        return center;
    }

    void PanZoom::setCenter(glm::vec2 center) {
        this->center = center;
    }

}
