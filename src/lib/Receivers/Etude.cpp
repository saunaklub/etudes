/*

  Études Audiovisuel - Graphical elements for audiovisual composition.
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

#include <Utility/Logging.hpp>

#include "Etude.hpp"

namespace etudes {

    using std::string;
    using namespace gl;

    using logging::LogLevel;
    using namespace util;

    void
    Etude::registerInputs() {
        registerInput("/background", vec_float_t{0.0f, 0.0f, 0.0f, 1.0f});
    }

    void
    Etude::init() {
        for(auto &element : elements) {
            element.second->init();
        }
    }

    void
    Etude::update() {
        for(auto &element : elements) {
            element.second->update();
        }
    }

    void
    Etude::addElement(std::string name,
                           std::unique_ptr<Element> element) {
        elements.push_back(std::make_pair(name, std::move(element)));
    }

    bool
    Etude::dispatchValue(std::string path, const vec_int_t &value) {
        return dispatchValueT(path, value);
    }

    bool
    Etude::dispatchValue(std::string path, const vec_float_t &value) {
        return dispatchValueT(path, value);
    }

    bool
    Etude::dispatchValue(std::string path, const vec_string_t &value) {
        return dispatchValueT(path, value);
    }

    template <typename T> bool
    Etude::dispatchValueT(std::string path, const T &value) {
        if(! Receiver::dispatchValue(path, value)) {
            string prefix = splitStringFirst(path);
            auto iter = std::find_if(elements.begin(), elements.end(),
                                     [&](const auto &e)  {
                                         return(e.first == prefix);
                                     });
            if(iter != elements.end()) {
                iter->second->setValue(splitStringRest(path), value);
                return true;
            }
        }

        logging::log(
            LogLevel::warning,
            "Etude::dispatchValue: Unable to dispatch message with path: " +
            path);
        return false;
    }

    void Etude::draw() {
        clearBackground();

        for(auto &element : elements) {
            element.second->draw();
        }
    }

    void Etude::clearBackground() {
        auto colorBackground = getValue<glm::vec4>("/background");

        getPainter().setColor(colorBackground);
        getPainter().rect({0, 0}, {1, 1});
    }

}
