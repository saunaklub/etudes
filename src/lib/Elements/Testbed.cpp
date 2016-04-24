#include <Graphics/Painter.hpp>

#include <Graphics/Geometry/Transforms.hpp>

#include "Testbed.hpp"

namespace etudes {
    void Testbed::registerInputs() {
        //registerInput("/test", {0.0f});
    }

    void Testbed::draw(const Context &context,
                       const Painter &painter) {
        const Rect &viewport = context.getViewport2D();
        glm::vec2 p0 = denormalize({0.0, 0.5}, viewport);
        glm::vec2 p1 = denormalize({1.0, 0.5}, viewport);

        painter.drawLine(p0, p1, 10, {1, 0.5, 0, 1});
    }
}
