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

#include <Utility/Logging.hpp>

#include "VideoOutput.hpp"

using namespace gl;

namespace etudes {

    using logging::log;
    using logging::LogLevel;

    VideoOutput::VideoOutput(std::string name,
                             int width, int height) :
        name(name),
        width(width),
        height(height),
        scene(nullptr) {
    }

    VideoOutput::~VideoOutput() {}

    std::string VideoOutput::getName() const {
        return name;
    }

    int VideoOutput::getWidth() const {
        return width;
    }

    int VideoOutput::getHeight() const {
        return height;
    }

    Scene * VideoOutput::getScene() const {
        return scene;
    }

}
