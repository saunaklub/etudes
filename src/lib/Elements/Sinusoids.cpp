#include <glbinding/gl/gl.h>
#include <glm/vec2.hpp>

#include <Utility/Logging.hpp>

#include <Graphics/Geometry/Transforms.hpp>
#include <Graphics/Painter.hpp>

#include "Sinusoids.hpp"

namespace etudes {

    using namespace gl;
    using logging::LogLevel;

    std::map<std::string, Sinusoids::DrawMode> mapDrawMode {
        {"straight", Sinusoids::STRAIGHT},
        {"circular", Sinusoids::CIRCULAR},
    };

    std::map<std::string, Sinusoids::OffsetMode> mapOffsetMode {
        {"absolute", Sinusoids::ABSOLUTE},
        {"increment", Sinusoids::INCREMENT},
        {"increment-falloff", Sinusoids::INCREMENT_FALLOFF},
    };

    void Sinusoids::registerInputs() {
        registerInput("/amplitudes", vec_float_t{1.0f});
        registerInput("/draw-mode", vec_string_t{"circular"});

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

    void Sinusoids::update() {
        amplitudes = getValue<vec_float_t>("/amplitudes");
        offsets = calculateOffsets(offsetMode, amplitudes);

        center = getValue<glm::vec2>("/center");

        widthBase = getValue<float>("/width");
        widthAmp = getValue<float>("/width-amp");

        colorBase = getValue<glm::vec4>("/color");
        colorAmp = getValue<glm::vec4>("/color-amp");

        time = seconds();
        freq = getValue<float>("/freq");
        lambda = getValue<float>("/lambda");
        phaseBase = getValue<float>("/phase");
        phaseAmp = getValue<float>("/phase-amp");

        strokeWidth = getValue<float>("/stroke-width");
        strokeBlur = getValue<float>("/stroke-blur");

        drawMode = mapDrawMode[getValue<std::string>("/draw-mode")];
        offsetMode = mapOffsetMode[getValue<std::string>("/offset-mode")];
    }

    void Sinusoids::draw(const Context &context,
                         const Painter &painter) {

        for(int index = amplitudes.size()-1 ; index >= 0 ; index--) {
            float amplitude = amplitudes[index];

            colorDraw = colorBase + colorAmp * amplitude;
            phaseDraw = phaseBase + phaseAmp * amplitude;

            switch(drawMode) {
            case STRAIGHT:
                drawSinusoidStraight(index, context, painter);
                break;

            case MIRRORED:
                drawSinusoidStraight(index, context, painter);
                break;

            case CIRCULAR:
                drawSinusoidCircular(index, context, painter);
                break;
            }
        }
    }

    std::vector<float>
    Sinusoids::calculateOffsets(OffsetMode offsetMode,
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

    void Sinusoids::drawSinusoidStraight(
        int index, const Context &context, const Painter &painter) {

        const Rect &viewport = context.getViewport2D();
        glm::vec2 start, end;

        float yStart = 0.f;
        float yEnd = 1.f;

        widthDraw = viewport.getDiagonal() / 2.0f *
            (widthBase + widthAmp * amplitudes[index]);

        start = glm::vec2(center[0] + offsets[index], yStart);
        end = glm::vec2(center[0] + offsets[index], yEnd);
        start = denormalize(start, viewport);
        end = denormalize(end, viewport);

        painter.sinusoidStraight(
            start, end, index+1,
            widthDraw, colorDraw,
            time, freq, lambda, phaseDraw + 0.0f,
            strokeWidth, strokeBlur);
    }

    void Sinusoids::drawSinusoidMirrored(
        int index, const Context &context, const Painter &painter) {

        const Rect &viewport = context.getViewport2D();
        glm::vec2 start, end;

        float yStart = 0.f;
        float yEnd = 1.f;

        widthDraw = viewport.getDiagonal() / 2.0f *
            (widthBase + widthAmp * amplitudes[index]);

        start = glm::vec2(center[0] + offsets[index], yStart);
        end = glm::vec2(center[0] + offsets[index], yEnd);
        start = denormalize(start, viewport);
        end = denormalize(end, viewport);

        painter.sinusoidStraight(
            start, end, index+1,
            widthDraw, colorDraw,
            time, freq, lambda, phaseDraw + 0.0f,
            strokeWidth, strokeBlur);

        start = glm::vec2(center[0] - offsets[index], yStart);
        end = glm::vec2(center[0] - offsets[index], yEnd);
        start = denormalize(start, viewport);
        end = denormalize(end, viewport);

        painter.sinusoidStraight(
            start, end, index+1,
            widthDraw, colorDraw,
            time, freq, lambda, phaseDraw + 0.5f,
            strokeWidth, strokeBlur);
    }

    void Sinusoids::drawSinusoidCircular(
        int index, const Context &context, const Painter &painter) {

        const Rect &viewport = context.getViewport2D();

        widthDraw = viewport.getDiagonal() / 2.0f *
            (widthBase + widthAmp * amplitudes[index] +
             offsets[index]);

        painter.sinusoidCircular(
            denormalize(center, viewport), index+1,
            widthDraw, widthDraw, colorDraw,
            time, freq, lambda, phaseDraw,
            strokeWidth, strokeBlur);
    }
}
