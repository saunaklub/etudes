#import "Syphon/Syphon.h"
#import "VideoOutputSyphon.h"

namespace etudes{

    VideoOutputSyphon::VideoOutputSyphon(std::string name, Scene * scene,
            int width, int height) :
        VideoOutput(scene, width, height) {
            server = [[SyphonServer alloc] 
                initWithName:[NSString stringWithCSring:name.c_str()]
                context:nil options:nil];
        }

    VideoOutputSyphon::~VideoOutputSyphon(){
        [server stop];
        [server release];
    }

    VideoOutputSyphon::writeOutput(){
        [server publishFrameTexture:idTexture
        textureTarget:GL_TEXTURE_RECTANGLE_EXT 
        imageRegion:NSMakeRect(0, 0, width, height)
        textureDimensions:NSMakeSize(width, height) 
        flipped:NO];
    }
}
