#include <Utility/Logging.hpp>

#include "VideoOutputV4L2.hpp"

namespace etudes {

    using logging::log;
    using logging::LogLevel;

    VideoOutputV4L2::VideoOutputV4L2(Etude *etude) :
        VideoOutput(etude) {
    }

    void VideoOutputV4L2::writeOutput() {
    }

}
