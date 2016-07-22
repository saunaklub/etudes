#include "Element.hpp"

namespace etudes  {
    const Context & Element::getContext() {
        return *context;
    }

    Painter & Element::getPainter() {
        return *painter;
    }
}
