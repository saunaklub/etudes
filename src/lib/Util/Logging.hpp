/*

  Études Audiovisuel - graphical elements for audiovisual composition
  Copyright (C) 2015 Patric Schmitz, Claudio Cabral

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

#ifndef ETUDES_LOGGING
#define ETUDES_LOGGING

#include <string>
#include <iostream>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using namespace std::literals::string_literals;

namespace etudes {
    namespace logging {

        enum LogLevel {
            none,
            info,
            warning,
            error,
            debug,
            excessive
        };

        template <typename T>
        void log(LogLevel level, const T &object);

        std::string to_string(const glm::vec2 &vec);
        std::string to_string(const glm::vec3 &vec);

        template <typename T>
        void log(LogLevel level, const T &object) {
            using std::cout;
            using std::cerr;
            using std::endl;

            switch(level) {
            case error:
                cerr << "ERROR: " << object << endl;
                break;
            case warning:
                cerr << "WARNING: " << object << endl;
                break;
            case info:
                cerr << "INFO: " << object << endl;
                break;
            case debug:
                cerr << "DEBUG: " << object << endl;
                break;
            case excessive:
                cerr << object << endl;
                break;
            default:
                break;
            }
        }

    }
}

#endif // ETUDES_LOGGING
