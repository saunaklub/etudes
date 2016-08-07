#import "Syphon/Syphon.h"
#import "VideoOutputSyphon.h"

namespace etudes{

    VideoOutputSyphon::VideoOutputSyphon(std::string name, Scene * scene,
            int width, int height) :
        VideoOutput(scene, width, height) {
            server = [[SyphonServer alloc] 
                initWithName:[NSString stringWithCSring:name.c_str()]
                context:myContext options:nil];

        }

    VideoOutputSyphon::~VideoOutputSyphon(){
        [server stop];
        [server release];
    }

    VideoOutputSyphon::writeOutput(){
        [server publishFrameTexture:idTexture,
        [NSRect],
        [NSSize 5],
        [BOOL true],
        ];

    }
}
