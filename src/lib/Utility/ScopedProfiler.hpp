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
