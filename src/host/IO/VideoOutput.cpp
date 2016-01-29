#include <Utility/Logging.hpp>

#include <Receivers/Etude.hpp>

#include "VideoOutput.hpp"

namespace etudes {

    using logging::log;
    using logging::LogLevel;

    VideoOutput::VideoOutput(Etude *etude) :
        etude(etude) {
    }

    VideoOutput::~VideoOutput() {}

    void VideoOutput::render() {
        bindFBO();

        etude->draw();

        readFBO();

        writeOutput();
    }

    void VideoOutput::bindFBO() {
    }

    void VideoOutput::readFBO() {
    }

}
