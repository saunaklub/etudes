#include "Utility.hpp"

namespace etudes {

    glm::vec3 to_vec3(const std::vector<float> &vec) {
        return glm::vec3(vec[0], vec[1], vec[2]);
    }

    std::string splitStringFirst(std::string str, char separator) {
        return str.substr(1, str.find(separator, 1) - 1);
    }

    std::string splitStringRest(std::string str, char separator) {
        return str.substr(str.find(separator, 1),
                          str.size() - str.find(separator, 1));
    }

}
