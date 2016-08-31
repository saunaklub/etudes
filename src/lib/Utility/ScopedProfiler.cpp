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

#include <iostream>

#include "ScopedProfiler.hpp"

namespace etudes {

    using logging::log;
    using logging::LogLevel;

    ScopedProfiler::ScopedProfiler(std::string prefix,
                                   LogLevel loglevel) :
        prefix(prefix),
        loglevel(loglevel) {

        start = clock.now();
    }

    ScopedProfiler::~ScopedProfiler() {
        if(prefix != "")
            std::cout << prefix << ": ";

        Duration duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                clock.now() - start);
        log(loglevel, std::to_string(duration.count()) + " ms");
    }

}
