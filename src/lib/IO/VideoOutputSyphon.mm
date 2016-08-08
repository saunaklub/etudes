#import "VideoOutputSyphon.h"
#import "Syphon/Syphon.h"

namespace etudes{

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

    void VideoOutputSyphon::writeOutput(){
        auto idTex = getTextureId();

	[server->syphon publishFrameTexture:idTex
	textureTarget:GL_TEXTURE_2D
	imageRegion:NSMakeRect(0, 0, width, height)
	textureDimensions:NSMakeSize(width, height)
	flipped:NO];
    }

    void VideoOutputSyphon::createOutput(std::string outputId) {

        auto ctx =  CGLGetCurrentContext();
        server->syphon = [[SyphonServer alloc]
            initWithName:[NSString stringWithCString:outputId.c_str()]
            context:ctx options:nil];

    }
}
