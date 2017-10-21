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
        output = std::make_unique<VideoOutputV4L2>(scene.get(), width, height);
#elif defined DARWIN
        output = std::make_unique<VideoOutputSyphon>(scene.get(), width, height);
#elif defined WINDOWS
        output = std::make_unique<VideoOutputSpout>(scene.get(), width, height);
#endif
        output->createOutput(name);
    }

    void Renderer::renderOutput() {
        if(output)
            output->render();
    }

}
