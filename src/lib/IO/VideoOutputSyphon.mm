#import "VideoOutputSyphon.h"

namespace etudes{

    VideoOutputSyphon::VideoOutputSyphon(std::string name, Scene * scene,
	                    int width, int height) :
	                    VideoOutput(scene, width, height) {

            auto * window = glfwGetCurrentContext();
            auto  * context = glfwGetNSGLContext(window);

    CGLContextObj ctx =  [context CGLContextObj];
	    server = [[SyphonServer alloc]
		initWithName:[NSString stringWithCString:name.c_str()]
		context:ctx options:nil];
     }

    VideoOutputSyphon::~VideoOutputSyphon(){
	[server stop];
	[server release];
    }

    void VideoOutputSyphon::writeOutput(){
        auto idTex = getTextureId();
	[server publishFrameTexture:idTex
	textureTarget:GL_TEXTURE_RECTANGLE_EXT
	imageRegion:NSMakeRect(0, 0, width, height)
	textureDimensions:NSMakeSize(width, height)
	flipped:NO];
    }
    void VideoOutputSyphon::createOutput(std::string outputId) {

    }
}
