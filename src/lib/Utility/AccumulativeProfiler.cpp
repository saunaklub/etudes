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
