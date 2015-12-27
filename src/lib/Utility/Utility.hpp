#ifndef ETUDES_UTILITY
#define ETUDES_UTILITY

#include <vector>
#include <iostream>
#include <glm/vec3.hpp>

#ifdef DEBUG
#define EDB(x) std::cout << std::fixed << #x ": " << x << std::endl
#else
#define EDB(x)
#endif

namespace etudes {
    glm::vec3 to_vec3(const std::vector<float> &vec);
}

#endif // ETUDES_UTILITY
