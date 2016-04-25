#include <Utility/Logging.hpp>

#include <Graphics/Painter.hpp>
#include <Graphics/Geometry/Transforms.hpp>

#include "Testbed.hpp"

namespace etudes {
    using logging::LogLevel;

    void Testbed::registerInputs() {
        registerInput("/test", {});
    }

    void Testbed::draw(const Context &context,
                       const Painter &painter) {
        auto input = getValue<vec_t>("/test");

        const Rect &viewport = context.getViewport2D();
        glm::vec2 p0 = denormalize({0.0, 0.5}, viewport);
        glm::vec2 p1 = denormalize({1.0, 0.5}, viewport);

        painter.line(p0, p1, 20, {0, 1, 0, 1});
        painter.line(p0, p1, 1, {1, 0, 0, 1});
    }
}
