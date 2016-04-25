#ifndef ETUDES_UTILITY
#define ETUDES_UTILITY

#include <vector>
#include <list>
#include <iostream>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>

#include <glbinding/gl/gl.h>

#ifdef DEBUG
#define EDB(x) std::cout << std::fixed << #x ": " << x << std::endl
#else
#define EDB(x)
#endif

namespace etudes {
    glm::vec2 to_vec2(const std::vector<float> &vec);
    glm::vec3 to_vec3(const std::vector<float> &vec);
    glm::vec4 to_vec4(const std::vector<float> &vec);

    std::string splitStringFirst(std::string str, char separator='/');
    std::string splitStringRest(std::string str, char separator='/');

    long microSeconds();
    double seconds();

    void checkGLError(std::string context);
    std::string getGLErrorMessage(const gl::GLenum error);

    template <typename T>
    std::ostream &operator<<(std::ostream &os,
                             const std::vector<T> &container) {
        for(auto &e : container)
            os << e << " ";
        os << std::endl;

        return os;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os,
                             const std::list<T> &container) {
        for(auto &e : container)
            os << e << " ";
        os << std::endl;

        return os;
    }

    std::ostream &operator<<(std::ostream &os,
                             const glm::vec2 &vec);
    std::ostream &operator<<(std::ostream &os,
                             const glm::vec3 &vec);
    std::ostream &operator<<(std::ostream &os,
                             const glm::vec4 &vec);
    std::ostream &operator<<(std::ostream &os,
                             const glm::mat4 &vec);

    // template <typename T>
    // std::string to_string(const T &t) {
    //     return t.toString();
    // }

}

#endif // ETUDES_UTILITY
