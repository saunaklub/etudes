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
        registerInput("/partials", vec_float_t{1.0f, 0.6f, 0.2f});

        registerInput("/mode", vec_string_t{"straight"});

        registerInput("/freq", vec_float_t{1.0f});
        registerInput("/lambda", vec_float_t{1.0f});
        registerInput("/phase-amp", vec_float_t{0.0f});

        registerInput("/stroke-width", vec_float_t{0.5f});
        registerInput("/stroke-blur", vec_float_t{0.0f});

        registerInput("/center", vec_float_t{0.5f, 0.5f});

        registerInput("/offset-mode", vec_string_t{"absolute"});
        registerInput("/offset-scale", vec_float_t{1.0f});

        registerInput("/color-base-red",   vec_float_t{1.0f});
        registerInput("/color-base-green", vec_float_t{1.0f});
        registerInput("/color-base-blue",  vec_float_t{1.0f});
        registerInput("/color-base-alpha", vec_float_t{1.0f});

        registerInput("/color-amp-red",   vec_float_t{0.0f});
        registerInput("/color-amp-green", vec_float_t{0.0f});
        registerInput("/color-amp-blue",  vec_float_t{0.0f});
        registerInput("/color-amp-alpha", vec_float_t{0.0f});
    }

    void PartialAura::draw(const Context &context,
                           const Painter &painter) {
        auto partials = getValue<vec_float_t>("/partials");
        auto freq = getValue<float>("/freq");
        auto lambda = getValue<float>("/lambda");

        const ShaderRegistry &registry = context.getShaderRegistry();
        const Rect &viewport = context.getViewport2D();

        const float sizeMax = 400;

        glm::vec2 center = getValue<glm::vec2>("/center");
        glm::vec2 start, end;

        float yStart = 0.f;
        float yEnd = 1.f;

        std::string mode = getValue<std::string>("/mode");
        std::string shader = "sinusoid";

        glUseProgram(registry.getProgram("sinusoid"));

        glUniform1f(registry.getUniform("sinusoid", "time"), seconds());
        glUniform1f(registry.getUniform("sinusoid", "freq"), freq);
        glUniform1f(registry.getUniform("sinusoid", "lambda"), lambda);
        glUniform1f(registry.getUniform("sinusoid", "stroke_width"),
                    getValue<float>("/stroke-width"));
        glUniform1f(registry.getUniform("sinusoid", "stroke_blur"),
                    getValue<float>("/stroke-blur"));

        float colorBaseRed   = getValue<float>("/color-base-red");
        float colorBaseGreen = getValue<float>("/color-base-green");
        float colorBaseBlue  = getValue<float>("/color-base-blue");
        float colorBaseAlpha = getValue<float>("/color-base-alpha");

        float colorAmpRed   = getValue<float>("/color-amp-red");
        float colorAmpGreen = getValue<float>("/color-amp-green");
        float colorAmpBlue  = getValue<float>("/color-amp-blue");
        float colorAmpAlpha = getValue<float>("/color-amp-alpha");

        float phaseAmp = getValue<float>("/phase-amp");

        std::vector<float> offsets = calculateOffsets(partials);

        for(int partial = partials.size()-1 ;
            partial >= 0 ; partial--) {
            float amplitude = partials[partial];

            glm::vec4 color(
                colorBaseRed   + colorAmpRed   * amplitude,
                colorBaseGreen + colorAmpGreen * amplitude,
                colorBaseBlue  + colorAmpBlue  * amplitude,
                colorBaseAlpha + colorAmpAlpha * amplitude);
            float size = sizeMax * amplitude;

            glUniform1i(registry.getUniform("sinusoid", "order"), partial+1);

            start = glm::vec2(center[0] - offsets[partial], yStart);
            end = glm::vec2(center[0] - offsets[partial], yEnd);

            start = denormalize(start, viewport);
            end = denormalize(end, viewport);

            glUniform1f(registry.getUniform("sinusoid", "phase"),
                        amplitude * phaseAmp);
            painter.sinusoid(start, end, size, color);

            start = glm::vec2(center[0] + offsets[partial], yStart);
            end = glm::vec2(center[0] + offsets[partial], yEnd);

            start = denormalize(start, viewport);
            end = denormalize(end, viewport);

            glUniform1f(registry.getUniform("sinusoid", "phase"),
                        .5f + amplitude * phaseAmp);
            painter.sinusoid(start, end, size, color);
        }
    }

    std::vector<float>
    PartialAura::calculateOffsets(const std::vector<float> &partials) {
        std::vector<float> offsets;
        offsets.resize(partials.size());

        float offset = 0.f;
        float offsetScale = getValue<float>("/offset-scale");
        std::string offsetMode = getValue<std::string>("/offset-mode");

        for(size_t partial = 0 ; partial < partials.size() ; ++partial) {
            float amplitude = partials[partial];

            if(offsetMode == "absolute") {
                offset = float(partial+1) / float(partials.size()) / 2.f;
            }
            else if(offsetMode == "increment-falloff") {
                offset += amplitude / float(partial+1);
            }

            offsets[partial] = offset * offsetScale;
        }

        return offsets;
    }
}
