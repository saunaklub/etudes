/*

  Études Audiovisuel - Graphical elements for audiovisual composition.
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

#import "VideoOutputSyphon.hpp"
#import "Syphon/Syphon.h"

namespace etudes {

    struct VideoOutputSyphon::Server {
        SyphonServer * syphon;
    };

    VideoOutputSyphon::VideoOutputSyphon(Scene * scene,
                                         int width, int height) :
    VideoOutput(scene, width, height) {
        server = std::make_unique<Server>();
    }

    VideoOutputSyphon::~VideoOutputSyphon(){
        [server->syphon stop];
        [server->syphon release];
    }

    void VideoOutputSyphon::render() {
        [server->syphon bindToDrawFrameOfSize:NSMakeSize(width, height)];
        drawScene();
        [server->syphon unbindAndPublish];
    }

    void VideoOutputSyphon::createOutput(std::string outputId) {
        auto ctx =  CGLGetCurrentContext();
        server->syphon = [[SyphonServer alloc]
            initWithName:[NSString stringWithCString:outputId.c_str()
            encoding: NSUTF8StringEncoding]
            context:ctx options:nil];
    }

}
