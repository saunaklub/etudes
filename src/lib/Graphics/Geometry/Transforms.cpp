#include "Transforms.hpp"

namespace etudes {

    glm::vec2 denormalize(const glm::vec2 &pos, const Rect &area) {
        glm::vec2 result;

        result[0] = area.getPosX() + pos[0] * area.getWidth();
        result[1] = area.getPosY() + pos[1] * area.getHeight();

        return result;
    }

}
