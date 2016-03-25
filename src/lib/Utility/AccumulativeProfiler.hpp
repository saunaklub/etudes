#ifndef ETUDES_ACCUMULATIVEPROFILER
#define ETUDES_ACCUMULATIVEPROFILER

#include <string>
#include <chrono>
#include <map>

namespace etudes {

    class AccumulativeProfiler {
    public:
        typedef std::chrono::high_resolution_clock::time_point TimePoint;
        typedef std::chrono::high_resolution_clock::duration   Duration;

        typedef std::map<std::string, TimePoint> MapStringTimepoint;
        typedef std::map<std::string, Duration> MapStringDuration;

        AccumulativeProfiler();

        /**
         * Start measuring time in the given section.
         *
         * @param section Timing section to use. Default is "default".
         */
        void start(std::string section="default");

        /**
         * Stop measuring time in the given section.
         *
         * @param section Timing section to use. Default is "default".
         */
        void stop(std::string section="default");

        /**
         * Return accumulative time spent in the given section. If
         * measurement is still running, stop() will be called
         * implicitly.
         *
         * @param section Timing section to use. Default is "default".
         * @return number of microseconds since start of measurement.
         */
        long elapsed(std::string section="default");

        /**
         * Reset all accumulated measurements.
         */
        void reset();

    private:
        std::chrono::high_resolution_clock clock;
        MapStringTimepoint mapActive;
        MapStringDuration mapAccumulated;
    };

}

#endif  // ETUDES_ACCUMULATIVEPROFILER
