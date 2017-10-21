#include <glbinding/gl/gl.h>

#include <Utility/Logging.hpp>
#include <Utility/Utility.hpp>

#include "VideoOutputSpout.hpp"

namespace etudes {

    using namespace gl;

    VideoOutputSpout::VideoOutputSpout(Scene *scene,
                                       int width, int height) :
        VideoOutput(scene, width, height) {
        initFBO();
    }

    void VideoOutputSpout::initFBO() {
        glGenTextures(1, &idTexture);
        glBindTexture(GL_TEXTURE_2D, idTexture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
            width, height, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        glGenFramebuffers(1, &idFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, idFBO);
        glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D, idTexture, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void VideoOutputSpout::createOutput(std::string outputId) {
        spoutptr = GetSpout();
        spoutptr->CreateSender(outputId.c_str(), width, height);
    }

    void VideoOutputSpout::render() {
        glBindFramebuffer(GL_FRAMEBUFFER, idFBO);
        drawScene();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        spoutptr->SendTexture(idTexture, gl::GLuint(GL_TEXTURE_2D), width, height);
    }

}