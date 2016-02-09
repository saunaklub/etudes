#ifndef ETUDES_VIDEOOUTPUT
#define ETUDES_VIDEOOUTPUT

#include <string>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

namespace etudes {
    class Etude;

    class VideoOutput {
    public:
        VideoOutput(Etude *etude, int width, int height);
        virtual ~VideoOutput();

        void render();

        virtual void createOutput(std::string outputId) = 0;
        virtual void writeOutput() = 0;

    protected:
        int width;
        int height;
        std::vector<char> data;

    private:
        void initFBO();
        void bindFBO();
        void readFBO();
        void unbindFBO();

        Etude *etude;

        gl::GLuint idFBO;
        gl::GLuint idTexture;
    };
}

#endif // ETUDES_VIDEOOUTPUT
