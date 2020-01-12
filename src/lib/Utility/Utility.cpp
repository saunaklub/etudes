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

#include <map>
#include <chrono>

#include <glad/glad.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include <Graphics/ShaderRegistry.hpp>
#include <Utility/Logging.hpp>

#include "Utility.hpp"

namespace etudes {
    namespace util {

        typedef std::chrono::steady_clock clock_t;
        using std::chrono::duration_cast;
        using std::chrono::duration;
        using std::chrono::microseconds;

        using logging::LogLevel;

        auto t0 = clock_t::now();

        std::map<GLenum, std::string> glErrorMap = {
            {GL_INVALID_ENUM, "GL_INVALID_ENUM"},
            {GL_INVALID_VALUE, "GL_INVALID_VALUE"},
            {GL_INVALID_OPERATION, "GL_INVALID_OPERATION"},
            {GL_OUT_OF_MEMORY, "GL_OUT_OF_MEMORY"},
            {GL_STACK_OVERFLOW, "GL_STACK_OVERFLOW"},
            {GL_STACK_UNDERFLOW, "GL_STACK_UNDERFLOW"},
            {GL_INVALID_FRAMEBUFFER_OPERATION, "GL_INVALID_FRAMEBUFFER_OPERATION"}
        };

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
            return str.substr(0, str.find(separator, 1));
        }

        std::string splitStringRest(std::string str, char separator) {
            return str.substr(str.find(separator, 1) + 1,
                              str.size() - str.find(separator, 1));
        }

        bool checkGLError(std::string context) {
            const GLenum e = glGetError();

            if (e == GL_NO_ERROR)
                return false;

            log(LogLevel::error,
                context + ": " + getGLErrorMessage(e));
            return true;
        }

        std::string getGLErrorMessage(const GLenum error) {
            if(glErrorMap.find(error) != glErrorMap.end())
                return glErrorMap[error];

            return "unknown error";
        }

        void registerDefaultShaders(ShaderRegistry & shaders) {
            shaders.registerShader("mvp-uv", GL_VERTEX_SHADER,
                                   {"resources/shaders/mvp-uv.vsh"});
            shaders.registerShader("ident", GL_VERTEX_SHADER,
                                   {"resources/shaders/ident.vsh"});

            shaders.registerShader("white", GL_FRAGMENT_SHADER,
                                   {"resources/shaders/white.fsh"});
            shaders.registerShader("solid", GL_FRAGMENT_SHADER,
                                   {"resources/shaders/solid.fsh"});
            shaders.registerShader("textured", GL_FRAGMENT_SHADER,
                                   {"resources/shaders/textured-hueshift.fsh"});

            shaders.registerProgram("simple", {"ident", "white"});

            shaders.registerProgram("textured", {"mvp-uv", "textured"});
            shaders.registerUniform("textured", "mvp");
            shaders.registerUniform("textured", "shiftHue");
            shaders.registerUniform("textured", "shiftSaturation");
            shaders.registerUniform("textured", "shiftValue");
            shaders.registerUniform("textured", "alpha");
            shaders.registerUniform("textured", "useAlpha");

            shaders.registerProgram("solid", {"mvp-uv", "solid"});
            shaders.registerUniform("solid", "mvp");
            shaders.registerUniform("solid", "color");
        }

        float deg2rad(float deg) {
            return deg / 180.f * glm::pi<float>();
        }

        float rad2deg(float rad) {
            return rad / glm::pi<float>() * 180.f;
        }
    }

    std::ostream &operator<<(std::ostream &os,
                             const glm::vec2 &t) {
        os << glm::to_string(t);
        return os;
    }
    std::ostream &operator<<(std::ostream &os,
                             const glm::vec3 &t) {
        os << glm::to_string(t);
        return os;
    }
    std::ostream &operator<<(std::ostream &os,
                             const glm::vec4 &t) {
        os << glm::to_string(t);
        return os;
    }

    std::ostream &operator<<(std::ostream &os,
                             const glm::mat4 &t) {
        os << glm::to_string(t);
        return os;
    }

    // template <typename T>
    // std::ostream &operator<<(std::ostream &os,
    //                          const T &t) {
    //     os << t.toString();
    //     return os;
    // }

}
