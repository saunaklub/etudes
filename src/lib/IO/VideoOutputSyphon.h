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

#ifndef ETUDES_VIDEOOUTPUTSYPHON
#define ETUDES_VIDEOOUTPUTSYPHON

#include <string>

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_NSGL
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFWAPI

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "VideoOutput.hpp"

namespace etudes {


    class VideoOutputSyphon : public VideoOutput {
        public:
            VideoOutputSyphon(Scene *scene, int width, int height);
            ~VideoOutputSyphon() override;

            void createOutput(std::string outputId) override;
            void writeOutput() override;

        private:

            struct Server * server;
    };

}

#endif // ETUDES_VIDEOOUTPUTSYPHON
