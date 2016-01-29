#ifndef ETUDES_VIDEOOUTPUT
#define ETUDES_VIDEOOUTPUT

namespace etudes {
    class Etude;

    class VideoOutput {
    public:
        VideoOutput(Etude *etude);
        virtual ~VideoOutput();

        void render();

    private:
        void bindFBO();
        void readFBO();

        virtual void writeOutput() = 0;

        Etude *etude;
    };
}

#endif // ETUDES_VIDEOOUTPUT
