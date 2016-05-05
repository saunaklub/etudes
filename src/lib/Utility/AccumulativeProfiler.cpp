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

#include <exception>

#include "AccumulativeProfiler.hpp"

namespace etudes {

    AccumulativeProfiler::AccumulativeProfiler() {

    }

    void AccumulativeProfiler::start(std::string section) {
        mapActive[section] = clock.now();
    }

    void AccumulativeProfiler::stop(std::string section) {
        if(mapActive.find(section) == mapActive.end() ||
           mapActive[section] == TimePoint()) {
            throw std::logic_error(
                std::string("AccumulativeProfiler: stop() "
                            "called before start(). section: ")
                + section);
        }
        else {
            mapAccumulated[section] += clock.now() - mapActive[section];
            mapActive[section] = TimePoint();
        }

    }

    long AccumulativeProfiler::elapsed(std::string section){
        if(mapActive[section] != TimePoint())
            stop(section);
        return std::chrono::duration_cast<std::chrono::microseconds>
            (mapAccumulated[section]).count();
    }

}
