#include <IO/VideoOutputV4L2.hpp>

#include "Renderer.hpp"

namespace etudes {

    Renderer::Renderer(std::string name,
                       std::unique_ptr<Etude> etude) :
        name(name),
        etude(std::move(etude)) {
    }

    std::string Renderer::getName() const {
        return name;
    }

    void Renderer::update() {
        etude->update();
    }

    void Renderer::render(Context &context, Painter &painter) {
        etude->draw(context, painter);
    }

    void Renderer::addOutput(std::string name, int width, int height) {
#ifdef LINUX
        output = std::make_unique<VideoOutputV4L2>(etude.get(), width, height);
        output->createOutput(name);
#endif
    }

    void Renderer::renderOutput(Context &context, Painter &painter) {
        if(output)
            output->render(context, painter);
    }

}
