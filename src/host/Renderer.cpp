#include <IO/VideoOutputV4L2.hpp>

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
        output->createOutput(name);
#elif defined DARWIN
        output = std::make_unique<VideoOutputSyphon>(scene.get(), width, height);
        output->createOutput(name);
#endif
    }

    void Renderer::renderOutput() {
        if(output)
            output->render();
    }

}
