/*

  Études Audiovisuel - Graphical elements for audiovisual composition.
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

    void VideoOutput::render(const Context &context,
                             const Painter &painter) {
        bindFBO();

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        etude->draw(context, painter);

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
                     GL_UNSIGNED_BYTE, nullptr);

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
