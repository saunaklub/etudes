/*

  Études Audiovisuelles - Graphical elements for audiovisual composition.
  Copyright (C) 2015-2016 Patric Schmitz

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

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

#include <EtudesConfig.hpp>

#ifdef DEBUG
#define EDB(x) std::cout << std::fixed << #x ": " << x << std::endl
#else
#define EDB(x)
#endif

namespace etudes {

    class ShaderRegistry;

    namespace util {
        glm::vec2 to_vec2(const std::vector<float> &vec);
        glm::vec3 to_vec3(const std::vector<float> &vec);
        glm::vec4 to_vec4(const std::vector<float> &vec);

        std::string splitStringFirst(std::string str, char separator='/');
        std::string splitStringRest(std::string str, char separator='/');

        ETUDES_EXPORT long microSeconds();
        double seconds();

        ETUDES_EXPORT void checkGLError(std::string context);
        std::string getGLErrorMessage(const gl::GLenum error);

        void registerDefaultShaders(ShaderRegistry & shaders);

        float deg2rad(float);
        float rad2deg(float);
    }

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
