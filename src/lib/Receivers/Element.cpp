#include "Utility/Utility.hpp"

#include "Element.hpp"

namespace etudes {

    Element::Element() {
        util::registerDefaultShaders(shaders);
    }

    void
    Element::setContext(const Context & context) {
        this->context = &context;
        painter.setContext(context);
    }

    const Context &
    Element::getContext() const {
        assert(context);
        return *context;
    }

    ShaderRegistry &
    Element::getShaderRegistry() {
        return shaders;
    }

    Painter &
    Element::getPainter() {
        return painter;
    }

}
