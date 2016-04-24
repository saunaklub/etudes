#ifndef ETUDES_TRANSFORMS
#define ETUDES_TRANSFORMS

#include <glm/vec2.hpp>

#include <Graphics/Geometry/Rect.hpp>

namespace etudes {
    glm::vec2 denormalize(const glm::vec2 &pos, const Rect &area);
}

#endif // ETUDES_TRANSFORMS
