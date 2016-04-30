#include <glbinding/gl/gl.h>
#include <glm/vec2.hpp>

#include <Utility/Logging.hpp>

#include <Graphics/Geometry/Transforms.hpp>
#include <Graphics/Painter.hpp>

#include "PartialAura.hpp"

namespace etudes {

    using namespace gl;
    using logging::LogLevel;

    std::map<std::string, PartialAura::DrawMode> mapDrawMode {
        {"straight", PartialAura::STRAIGHT},
        {"circular", PartialAura::CIRCULAR},
    };

    std::map<std::string, PartialAura::OffsetMode> mapOffsetMode {
        {"absolute", PartialAura::ABSOLUTE},
        {"increment", PartialAura::INCREMENT},
        {"increment-falloff", PartialAura::INCREMENT_FALLOFF},
    };

    void PartialAura::registerInputs() {
        registerInput("/amplitudes", vec_float_t{1.0f});

        registerInput("/mode", vec_string_t{"straight"});

        registerInput("/width", vec_float_t{0.5});

        registerInput("/freq", vec_float_t{1.0f});
        registerInput("/lambda", vec_float_t{1.0f});
        registerInput("/phase-amp", vec_float_t{0.0f});

        registerInput("/stroke-width", vec_float_t{0.5f});
        registerInput("/stroke-blur", vec_float_t{0.0f});

        registerInput("/center", vec_float_t{0.5f, 0.5f});

        registerInput("/offset-mode", vec_string_t{"absolute"});
        registerInput("/offset-scale", vec_float_t{1.0f});

        registerInput("/color-base", vec_float_t{1.0f, 1.0f, 1.0f, 1.0f});
        registerInput("/color-amp",  vec_float_t{0.0f, 0.0f, 0.0f, 0.0f});

    }

    void PartialAura::draw(const Context &context,
                           const Painter &painter) {
        const ShaderRegistry &registry = context.getShaderRegistry();
        const Rect &viewport = context.getViewport2D();

        const float diagonal =
            std::sqrt(viewport.getWidth() * viewport.getWidth() +
                      viewport.getHeight() * viewport.getHeight());
        const float maxWidth = diagonal * getValue<float>("/width");

        glm::vec2 center = getValue<glm::vec2>("/center");

        auto partials = getValue<vec_float_t>("/amplitudes");

        auto freq = getValue<float>("/freq");
        auto lambda = getValue<float>("/lambda");

        DrawMode drawMode = mapDrawMode[getValue<std::string>("/draw-mode")];
        OffsetMode offsetMode =
            mapOffsetMode[getValue<std::string>("/offset-mode")];

        std::vector<float> offsets;
        offsets.resize(partials.size());
        offsets = calculateOffsets(offsetMode, amplitudes);

        auto colorBase = getValue<glm::vec4>("/color-base");
        auto colorAmp = getValue<glm::vec4>("/color-amp");
        float phaseAmp = getValue<float>("/phase-amp");

        glUseProgram(registry.getProgram("sinusoid"));

        glUniform1f(registry.getUniform("sinusoid", "time"), seconds());
        glUniform1f(registry.getUniform("sinusoid", "freq"), freq);
        glUniform1f(registry.getUniform("sinusoid", "lambda"), lambda);
        glUniform1f(registry.getUniform("sinusoid", "stroke_width"),
                    getValue<float>("/stroke-width"));
        glUniform1f(registry.getUniform("sinusoid", "stroke_blur"),
                    getValue<float>("/stroke-blur"));

        for(int partial = amplitudes.size()-1 ;
            partial >= 0 ; partial--) {

            float amplitude = amplitudes[partial];

            glm::vec4 color = colorBase + colorAmp * amplitude;
            float size = maxWidth * amplitude;

            glUniform1i(registry.getUniform("sinusoid", "order"), partial+1);
            glUniform1f(registry.getUniform("sinusoid", "phase"),
                        amplitude * phaseAmp);

            switch(drawMode) {
            case STRAIGHT:
                drawSinusoidStraight();
            case CIRCULAR:
                drawSinusoidCircular();
                break;
            }
        }
    }

    std::vector<float>
    PartialAura::calculateOffsets(OffsetMode offsetMode,
                                  const std::vector<float> &amplitudes) {

        float offset = 0.f;
        float offsetScale = getValue<float>("/offset-scale");

        for(size_t partial = 0 ; partial < partials.size() ; ++partial) {
            float amplitude = partials[partial];

            switch(offsetMode) {
            case ABSOLUTE:
                offset = float(partial+1) / float(partials.size()) / 2.f;
                break;
            case INCREMENT:
                offset += amplitude;
                break;
            case INCREMENT_FALLOFF:
                offset += amplitude / float(partial+1);
                break;
            }

            offsets[partial] = offset * offsetScale;
        }

        return offsets;
    }

    void PartialAura::drawSinusoidStraight(glm::vec2 center,
                                           const std::vector<float> &offsets) {
        glm::vec2 start, end;

        float yStart = 0.f;
        float yEnd = 1.f;

        start = glm::vec2(center[0] - offsets[partial], yStart);
        end = glm::vec2(center[0] - offsets[partial], yEnd);
        start = denormalize(start, viewport);
        end = denormalize(end, viewport);
        painter.sinusoidStraight(start, end, size, color);

        glUniform1f(registry.getUniform("sinusoid", "phase"),
                    .5f + amplitude * phaseAmp);
        start = glm::vec2(center[0] + offsets[partial], yStart);
        end = glm::vec2(center[0] + offsets[partial], yEnd);
        start = denormalize(start, viewport);
        end = denormalize(end, viewport);

        painter.sinusoidStraight(start, end, size, color);
    }

    void PartialAura::drawSinusoidCircular() {
    }
}
