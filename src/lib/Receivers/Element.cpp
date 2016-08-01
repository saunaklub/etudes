#include "Element.hpp"

namespace etudes {

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

    Painter &
    Element::getPainter() {
        return painter;
    }

}
