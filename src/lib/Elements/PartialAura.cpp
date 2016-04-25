#include <glbinding/gl/gl.h>
#include <glm/vec2.hpp>

#include <Utility/Logging.hpp>

#include <Graphics/Geometry/Transforms.hpp>
#include <Graphics/Painter.hpp>

#include "PartialAura.hpp"

namespace etudes {

    using namespace gl;
    using logging::LogLevel;

    void PartialAura::registerInputs() {
        registerInput("/partials", {});
        registerInput("/f0", {300.f});
    }

    void PartialAura::draw(const Context &context,
                           const Painter &painter) {
        auto partials = getValue<vec_t>("/partials");
        auto f0 = getValue<float>("/f0");

        const ShaderRegistry &registry = context.getShaderRegistry();
        const Rect &viewport = context.getViewport2D();

        const float width = 400;

        glm::vec2 center = glm::vec2(0.5, 0.5);
        glm::vec2 start, end;

        float offset = 0.f;

        glUseProgram(registry.getProgram("sinusoid"));

        glUniform1f(registry.getUniform("sinusoid", "time"), seconds());
        glUniform1f(registry.getUniform("sinusoid", "f0"), f0);

        for(size_t partial = 0 ; partial < partials.size() ; ++partial) {
            float amplitude = partials[partial];
            offset += amplitude / float(partial+1);

            glm::vec4 color(1, amplitude*3, 0, amplitude*3);
            float size = width * amplitude;

            glUniform1i(registry.getUniform("sinusoid", "order"), partial+1);

            start = glm::vec2(center[0] - offset, 0);
            end = glm::vec2(center[0] - offset, 1);

            start = denormalize(start, viewport);
            end = denormalize(end, viewport);

            glUniform1f(registry.getUniform("sinusoid", "phase"), 0.f);
            painter.sinusoid(start, end, size, color);

            start = glm::vec2(center[0] + offset, 0);
            end = glm::vec2(center[0] + offset, 1);

            start = denormalize(start, viewport);
            end = denormalize(end, viewport);

            glUniform1f(registry.getUniform("sinusoid", "phase"), .5f);
            painter.sinusoid(start, end, size, color);
        }
    }
}
