#ifndef ETUDES_VIDEOOUTPUTV4L2
#define ETUDES_VIDEOOUTPUTV4L2

#include "VideoOutput.hpp"

struct v4l2_capability;

namespace etudes {

    class VideoOutputV4L2 : public VideoOutput {
    public:
        VideoOutputV4L2(Etude *etude, int width, int height);

        void createOutput(std::string outputId) override;
        void writeOutput() override;

    private:
        void printV4L2Capabilities(v4l2_capability *caps);
        void printV4L2Formats();

        int fd;
    };

}

#endif // ETUDES_VIDEOOUTPUTV4L2
