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
        registerInput("/draw-mode", vec_string_t{"straight"});

        registerInput("/center", vec_float_t{0.5f, 0.5f});

        registerInput("/width", vec_float_t{0.1});
        registerInput("/width-amp", vec_float_t{0.0});

        registerInput("/freq", vec_float_t{1.0f});
        registerInput("/lambda", vec_float_t{1.0f});
        registerInput("/phase", vec_float_t{0.0f});
        registerInput("/phase-amp", vec_float_t{0.0f});

        registerInput("/stroke-width", vec_float_t{0.5f});
        registerInput("/stroke-blur", vec_float_t{0.0f});

        registerInput("/offset-mode", vec_string_t{"absolute"});
        registerInput("/offset-scale", vec_float_t{1.0f});

        registerInput("/color", vec_float_t{1.0f, 1.0f, 1.0f, 1.0f});
        registerInput("/color-amp",  vec_float_t{0.0f, 0.0f, 0.0f, 0.0f});
    }

    void PartialAura::update() {
        amplitudes = getValue<vec_float_t>("/amplitudes");
        offsets = calculateOffsets(offsetMode, amplitudes);

        center = getValue<glm::vec2>("/center");

        widthBase = getValue<float>("/width");
        widthAmp = getValue<float>("/width-amp");

        colorBase = getValue<glm::vec4>("/color");
        colorAmp = getValue<glm::vec4>("/color-amp");

        freq = getValue<float>("/freq");
        lambda = getValue<float>("/lambda");
        phaseBase = getValue<float>("/phase");
        phaseAmp = getValue<float>("/phase-amp");

        drawMode = mapDrawMode[getValue<std::string>("/draw-mode")];
        offsetMode = mapOffsetMode[getValue<std::string>("/offset-mode")];
    }

    void PartialAura::draw(const Context &context,
                           const Painter &painter) {
        const ShaderRegistry &registry = context.getShaderRegistry();
        const Rect &viewport = context.getViewport2D();

        glUseProgram(registry.getProgram("sinusoid"));

        glUniform1f(registry.getUniform("sinusoid", "time"), seconds());
        glUniform1f(registry.getUniform("sinusoid", "freq"), freq);
        glUniform1f(registry.getUniform("sinusoid", "lambda"), lambda);
        glUniform1f(registry.getUniform("sinusoid", "stroke_width"),
                    getValue<float>("/stroke-width"));
        glUniform1f(registry.getUniform("sinusoid", "stroke_blur"),
                    getValue<float>("/stroke-blur"));

        for(int index = amplitudes.size()-1 ; index >= 0 ; index--) {
            float amplitude = amplitudes[index];

            widthDraw = viewport.getDiagonal() / 2.0f *
                (widthBase + widthAmp * amplitude);

            colorDraw = colorBase + colorAmp * amplitude;

            glUniform1i(registry.getUniform("sinusoid", "order"), index+1);

            switch(drawMode) {
            case STRAIGHT:
                drawSinusoidStraight(index, context, painter);

            case CIRCULAR:
                drawSinusoidCircular();
                break;
            }
        }
    }

    std::vector<float>
    PartialAura::calculateOffsets(OffsetMode offsetMode,
                                  const std::vector<float> &amplitudes) {
        std::vector<float> offsets;
        offsets.resize(amplitudes.size());

        float offset = 0.f;
        float offsetScale = getValue<float>("/offset-scale");

        for(size_t index = 0 ; index < amplitudes.size() ; ++index) {
            float amplitude = amplitudes[index];

            switch(offsetMode) {
            case ABSOLUTE:
                offset = float(index+1) / float(amplitudes.size()) / 2.f;
                break;
            case INCREMENT:
                offset += amplitude;
                break;
            case INCREMENT_FALLOFF:
                offset += amplitude / float(index+1);
                break;
            }

            offsets[index] = offset * offsetScale;
        }

        return offsets;
    }

    void PartialAura::drawSinusoidStraight(
        int index,
        const Context &context, const Painter &painter) {

        const ShaderRegistry &registry = context.getShaderRegistry();
        const Rect &viewport = context.getViewport2D();

        glm::vec2 start, end;

        float yStart = 0.f;
        float yEnd = 1.f;

        glUniform1f(registry.getUniform("sinusoid", "phase"),
                    0.0f + phaseBase + phaseAmp * amplitudes[index]);

        start = glm::vec2(center[0] - offsets[index], yStart);
        end = glm::vec2(center[0] - offsets[index], yEnd);
        start = denormalize(start, viewport);
        end = denormalize(end, viewport);
        painter.sinusoidStraight(start, end, widthDraw, colorDraw);

        glUniform1f(registry.getUniform("sinusoid", "phase"),
                    0.5f + phaseBase + phaseAmp * amplitudes[index]);

        start = glm::vec2(center[0] + offsets[index], yStart);
        end = glm::vec2(center[0] + offsets[index], yEnd);
        start = denormalize(start, viewport);
        end = denormalize(end, viewport);

        painter.sinusoidStraight(start, end, widthDraw, colorDraw);
    }

    void PartialAura::drawSinusoidCircular() {
    }
}
