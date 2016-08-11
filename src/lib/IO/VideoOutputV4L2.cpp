/*

  Études Audiovisuels - Graphical elements for audiovisual composition.
  Copyright (C) 2015-2016 Patric Schmitz

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <cstring>

#include <linux/videodev2.h>

#include <glbinding/gl/gl.h>

#include <Utility/Logging.hpp>
#include <Utility/Utility.hpp>

#include "VideoOutputV4L2.hpp"

namespace etudes {

    using namespace gl;

    using logging::log;
    using logging::LogLevel;

    VideoOutputV4L2::VideoOutputV4L2(Scene *scene,
                                     int width, int height) :
        VideoOutput(scene, width, height),
        fd(-1) {
        data.resize(width*height*4);
        initFBO();
    }

    void VideoOutputV4L2::printV4L2Capabilities(v4l2_capability *caps) {
        using std::to_string;

        log(LogLevel::debug, "V4L2 device capabilities:");

        log(LogLevel::debug, "Driver: "s +
            reinterpret_cast<char*>(caps->driver));
        log(LogLevel::debug, "Card: "s +
            reinterpret_cast<char*>(caps->card));
        log(LogLevel::debug, "Bus info: "s +
            reinterpret_cast<char*>(caps->bus_info));
        log(LogLevel::debug, "Version: "s +
            to_string((caps->version >> 16) & 0xFF) + "." +
            to_string((caps->version >> 8) & 0xFF) + "." +
            to_string(caps->version & 0xFF));
    }

    void VideoOutputV4L2::printV4L2Formats() {
        struct v4l2_fmtdesc format;

        format.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
        format.index = 0;

        log(LogLevel::excessive, "Supported formats:");

        while(ioctl(fd, VIDIOC_ENUM_FMT, &format) != -1) {
            log(LogLevel::excessive,
                char((format.pixelformat >> 0) & 0xff), false);
            log(LogLevel::excessive,
                char((format.pixelformat >> 8) & 0xff), false);
            log(LogLevel::excessive,
                char((format.pixelformat >> 16)  & 0xff), false);
            log(LogLevel::excessive,
                char((format.pixelformat >> 24)  & 0xff), false);
            log(LogLevel::excessive, " ", false);
            log(LogLevel::excessive,
                reinterpret_cast<char*>(format.description));
            ++format.index;
        }
    }

    void VideoOutputV4L2::initFBO() {
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
                     GL_UNSIGNED_BYTE, nullptr);

        glGenFramebuffers(1, &idFBO);
        bindFBO();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, idTexture, 0);
        unbindFBO();
    }

    void VideoOutputV4L2::bindFBO() {
        glBindFramebuffer(GL_FRAMEBUFFER, idFBO);
    }

    void VideoOutputV4L2::unbindFBO() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void VideoOutputV4L2::readFBO() {
        glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, &data[0]);
    }

    void VideoOutputV4L2::createOutput(std::string outputId) {
        using std::to_string;

        fd = open(outputId.c_str(), O_RDWR);
        if(fd <= 0) {
            log(LogLevel::error, "Cannot open v4l2 loopback device " +
                outputId + ": " + strerror(errno));
        }

        struct v4l2_capability caps;
        struct v4l2_format format;

        memset(&caps, 0, sizeof(caps));
        memset(&format, 0, sizeof(format));

        int res = ioctl(fd, VIDIOC_QUERYCAP, &caps);
        if( res < 0 ) {
            log(LogLevel::error, "VIDIOC_QUERYCAP failed");
        }

        printV4L2Capabilities(&caps);
        printV4L2Formats();

        format.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
        format.fmt.pix.width = width;
        format.fmt.pix.height = height;
        format.fmt.pix.pixelformat = V4L2_PIX_FMT_BGR24;
        format.fmt.pix.field = V4L2_FIELD_NONE;
        format.fmt.pix.bytesperline = width * 4;
        format.fmt.pix.colorspace = V4L2_COLORSPACE_SRGB;

        res = ioctl( fd, VIDIOC_S_FMT, &format );
        if( res < 0 ) {
            log(LogLevel::error, "Cannot set video format to " +
                to_string(width) + "x" + to_string(height) +
                " BGR32 SRGB colorspace: " + strerror(errno));
        }

        ioctl(fd, VIDIOC_G_FMT, &format);
        if(format.fmt.pix.width == 0 || format.fmt.pix.height == 0) {
            log(LogLevel::error, "Invalid video capture resolution: " +
                to_string(width) + "x" + to_string(height));
        }

    }

    void VideoOutputV4L2::render() {
        bindFBO();

        drawScene();

        readFBO();

        unbindFBO();

        int res = write(fd, &data[0], width*height*4);
        if(res < 0) {
            log(LogLevel::error, "Failed to write video output!");
        }
    }
}
