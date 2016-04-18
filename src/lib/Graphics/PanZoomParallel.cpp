#include "PanZoomParallel.hpp"

namespace etudes {

    glm::vec2 PanZoomParallel::getXRange() {
        return {0, 1};
    }

    glm::vec2 PanZoomParallel::getYRange() {
        return glm::vec2{0, 1} / getAspectRatio();
    }

}
