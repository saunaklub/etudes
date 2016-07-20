#include <IO/VideoOutputV4L2.hpp>

#include "Renderer.hpp"

namespace etudes {

    Renderer::Renderer(std::string name,
                       std::shared_ptr<Etude> etude) :
        name(name),
        etude(etude) {
    }

    std::string Renderer::getName() const {
        return name;
    }

    void Renderer::update() {
        etude->update();
    }

    void Renderer::render() {
        etude->draw();
    }

    void Renderer::addOutput(std::string name, int width, int height) {
#ifdef LINUX
        output = std::make_unique<VideoOutputV4L2>(etude.get(), width, height);
        output->createOutput(name);
#endif
    }

    void Renderer::renderOutput() {
        if(output)
            output->render();
    }

}
