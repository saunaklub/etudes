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

#include <string>

#include <Utility/Logging.hpp>

namespace etudes {
    namespace logging {

        LogLevel logLevelMax = LogLevel::excessive;

        std::string to_string(const glm::vec2 &vec) {
            return "("s + std::to_string(vec[0]) +
                ", "s + std::to_string(vec[1]) + ")"s;
        }

        std::string to_string(const glm::vec3 &vec) {
            return "("s + std::to_string(vec[0]) +
                ", "s + std::to_string(vec[1]) +
                ", "s + std::to_string(vec[2]) + ")"s;
        }

        void setLogLevelMax(LogLevel logLevel) {
            logLevelMax = logLevel;
        }
    }
}
