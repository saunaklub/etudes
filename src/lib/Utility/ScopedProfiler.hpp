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

#ifndef ETUDES_SCOPEDPROFILER
#define ETUDES_SCOPEDPROFILER

#include <chrono>
#include <string>

#include <Utility/Logging.hpp>

namespace etudes {

    class ScopedProfiler {
    public:
        typedef std::chrono::high_resolution_clock Clock;
        typedef std::chrono::high_resolution_clock::time_point TimePoint;
        typedef std::chrono::high_resolution_clock::duration Duration;

        ScopedProfiler(std::string prefix="",
                       logging::LogLevel loglevel=logging::debug);

        ~ScopedProfiler();

    private:
        std::string prefix;
        logging::LogLevel loglevel;

        Clock clock;
        TimePoint start;
    };

}

#endif  // ETUDES_SCOPEDPROFILER
