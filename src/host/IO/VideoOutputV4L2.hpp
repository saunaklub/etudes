#ifndef ETUDES_VIDEOOUTPUTV4L2
#define ETUDES_VIDEOOUTPUTV4L2

#include "VideoOutput.hpp"

namespace etudes {
    class VideoOutputV4L2 : public VideoOutput {
    public:
        VideoOutputV4L2(Etude *etude);

        void writeOutput() override;

    private:
    };
}

#endif // ETUDES_VIDEOOUTPUTV4L2
