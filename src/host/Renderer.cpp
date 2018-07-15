#ifdef LINUX
#include <IO/VideoOutputV4L2.hpp>
#elif defined DARWIN
#include <IO/VideoOutputSyphon.hpp>
#elif defined WINDOWS
#include <IO/VideoOutputSpout.hpp>
#endif

#include "Renderer.hpp"

namespace etudes {

    Renderer::Renderer(std::string name,
                       std::unique_ptr<Scene> scene) :
        name(name),
        scene(std::move(scene)) {
    }

    std::string Renderer::getName() const {
        return name;
    }

    void Renderer::update() {
        scene->update();
    }

    void Renderer::render() {
        scene->draw();
    }

    void Renderer::setOutput(std::string name, int width, int height) {
#if defined LINUX
        output = std::make_unique<VideoOutputV4L2>(name, width, height);
#elif defined DARWIN
        output = std::make_unique<VideoOutputSyphon>(name, width, height);
#elif defined WINDOWS
        output = std::make_unique<VideoOutputSpout>(name, width, height);
#endif
        output->create();
    }

    void Renderer::renderOutput() {
        if(output)
            output->render();
    }

}
