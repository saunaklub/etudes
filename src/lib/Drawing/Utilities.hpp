#ifndef ETUDES_UTILITIES
#define ETUDES_UTILITIES

#include <vector>
#include <glm/vec3.hpp>

namespace etudes {
    glm::vec3 to_vec3(const std::vector<float> &vec) {
        return glm::vec3(vec[0], vec[1], vec[2]);
    }
}

#endif // ETUDES_UTILITIES
