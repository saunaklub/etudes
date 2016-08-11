/*

   Études Audiovisuels - Graphical elements for audiovisual composition.
   Copyright (C) 2016 Claudio Cabral

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

#include <memory>
#include <string>

#include "VideoOutput.hpp"

namespace etudes {

    class VideoOutputSyphon : public VideoOutput {
        public:
            VideoOutputSyphon(Scene *scene, int width, int height);
            ~VideoOutputSyphon() override;

            void createOutput(std::string outputId) override;
            void render() override;

        private:
            struct Server;
            std::unique_ptr<Server> server;
    };

}

#endif // ETUDES_VIDEOOUTPUTSYPHON
