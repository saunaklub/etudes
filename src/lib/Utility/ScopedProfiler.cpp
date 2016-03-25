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
