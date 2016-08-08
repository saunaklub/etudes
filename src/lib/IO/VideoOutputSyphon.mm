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

    void VideoOutputSyphon::render(){

        [server->syphon bindToDrawFrameOfSize:NSMakeSize(width,height)];

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
