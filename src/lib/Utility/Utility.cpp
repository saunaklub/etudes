#include <chrono>

#include "Utility.hpp"

namespace etudes {

    typedef std::chrono::steady_clock clock_t;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::microseconds;

    auto t0 = clock_t::now();

    long microSeconds() {
        auto diff =  duration_cast<microseconds>(clock_t::now() - t0);
        return diff.count();
    }

    double seconds() {
        return microSeconds() / 1000000.0;
    }

    glm::vec2 to_vec2(const std::vector<float> &vec) {
        return glm::vec2(vec[0], vec[1]);
    }

    glm::vec3 to_vec3(const std::vector<float> &vec) {
        return glm::vec3(vec[0], vec[1], vec[2]);
    }

    glm::vec4 to_vec4(const std::vector<float> &vec) {
        return glm::vec4(vec[0], vec[1], vec[2], vec[3]);
    }

    std::string splitStringFirst(std::string str, char separator) {
        return str.substr(1, str.find(separator, 1) - 1);
    }

    std::string splitStringRest(std::string str, char separator) {
        return str.substr(str.find(separator, 1),
                          str.size() - str.find(separator, 1));
    }

}
