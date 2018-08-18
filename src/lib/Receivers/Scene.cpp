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

#include <algorithm>
#include <string>

#include <glbinding/gl/gl.h>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>

#include "Scene.hpp"

namespace  {
    using namespace gl;

    const std::vector<gl::GLenum> blendingFactors =  {
        GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR,
        GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,
        GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA,
        GL_ONE_MINUS_CONSTANT_ALPHA, GL_SRC_ALPHA_SATURATE
    };

    gl::GLenum getBlendFactorByNormalizedFloat(float f) {
        return blendingFactors[size_t(f * (blendingFactors.size()-1))];
    }

    float getNormalizedFloatByBlendFactor(gl::GLenum factor) {
        for(size_t i = 0 ; i < blendingFactors.size() ; i++) {
            if(factor == blendingFactors[i]) {
                return i / float(blendingFactors.size() - 1);
            }
        }
        return -1.f;
    }

}

namespace etudes {

    using std::string;
    using namespace gl;

    using logging::LogLevel;
    using namespace util;

    void
    Scene::registerInputs() {
        registerInput("background", vec_float_t{0.0f, 0.0f, 0.0f, 1.0f});

        auto source = getNormalizedFloatByBlendFactor(GL_SRC_ALPHA);
        auto dest = getNormalizedFloatByBlendFactor(GL_ONE_MINUS_SRC_ALPHA);
        registerInput("blend-source", vec_float_t{source});
        registerInput("blend-dest", vec_float_t{dest});
        registerInput("blend-enabled", vec_float_t{0.0f});
    }

    void
    Scene::init() {
        for(auto &element : elements) {
            element.second->setContext(getContext());
            element.second->init();
        }
    }

    void
    Scene::update() {
        for(auto &element : elements) {
            element.second->update();
        }
    }

    void
    Scene::addElement(std::string name,
                           std::unique_ptr<Element> element) {
        elements.push_back(std::make_pair(name, std::move(element)));
    }

    bool
    Scene::dispatchValue(std::string path, const vec_int_t &value) {
        return dispatchValueT(path, value);
    }

    bool
    Scene::dispatchValue(std::string path, const vec_float_t &value) {
        return dispatchValueT(path, value);
    }

    bool
    Scene::dispatchValue(std::string path, const vec_string_t &value) {
        return dispatchValueT(path, value);
    }

    template <typename T> bool
    Scene::dispatchValueT(std::string path, const T &value) {
        if(Receiver::dispatchValue(path, value))
            return true;

        string prefix = splitStringFirst(path);
        auto iter = std::find_if(elements.begin(), elements.end(),
                                 [&](const auto &e)  {
                                     return(e.first == prefix);
                                 });
        if(iter != elements.end()) {
            iter->second->setValue(splitStringRest(path), value);
            return true;
        }

        logging::log(
            LogLevel::warning,
            "Scene::dispatchValue: Unable to dispatch message with path: " +
            path);

        return false;
    }

    void Scene::draw() {
        clearBackground();
        setBlendFunc();

        for(auto &element : elements) {
            element.second->draw();
        }
    }

    void Scene::clearBackground() {
        auto colorBackground = getValue<glm::vec4>("background");

        getPainter().setColor(colorBackground);
        getPainter().drawRect({0, 0}, {1, 1});
    }

    void Scene::setBlendFunc() {
        auto blendSource =
            getBlendFactorByNormalizedFloat(getValue<float>("blend-source"));
        auto blendDest =
            getBlendFactorByNormalizedFloat(getValue<float>("blend-dest"));

        if(getValue<float>("blend-enabled") != 0.0f)
            glBlendFunc(blendSource, blendDest);
        else
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}
