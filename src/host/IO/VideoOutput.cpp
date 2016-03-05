#include <Utility/Logging.hpp>

#include <Receivers/Etude.hpp>

#include "VideoOutput.hpp"

using namespace gl;

namespace etudes {

    using logging::log;
    using logging::LogLevel;

    VideoOutput::VideoOutput(Etude *etude,
                             int width, int height) :
        width(width),
        height(height),
        etude(etude) {
        data.resize(width*height*4);
        initFBO();
    }

    VideoOutput::~VideoOutput() {}

    void VideoOutput::render(const ShaderRegistry &registry,
                             const Painter &painter) {
        bindFBO();

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        etude->draw(registry, painter);

        readFBO();
        unbindFBO();

        writeOutput();
    }

    void VideoOutput::initFBO() {
        glGenTextures(1, &idTexture);
        glBindTexture(GL_TEXTURE_2D, idTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GLint(GL_REPEAT));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GLint(GL_REPEAT));
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER, GLint(GL_NEAREST));
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MAG_FILTER, GLint(GL_NEAREST));
        glTexImage2D(GL_TEXTURE_2D, 0, GLint(GL_SRGB8),
                     width, height, 0, GL_BGR,
                     GL_UNSIGNED_BYTE, NULL);

        glGenFramebuffers(1, &idFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, idFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, idTexture, 0 );
    }

    void VideoOutput::bindFBO() {
        glBindFramebuffer(GL_FRAMEBUFFER, idFBO);
    }

    void VideoOutput::unbindFBO() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void VideoOutput::readFBO() {
        glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, &data[0]);
    }

}
