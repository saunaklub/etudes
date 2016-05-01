#include <functional>

#include <glbinding/gl/gl.h>
using namespace gl;

#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>

#include <Graphics/Context.hpp>
#include <Graphics/Geometry/Transforms.hpp>

#include "Painter.hpp"

namespace etudes {

    using logging::LogLevel;

    const std::string shaderLine = "line";
    const std::string shaderSinusoid = "sinusoid";

    Painter::Painter(const Context &context) :
        context(context) {
    }

    void Painter::init() {
    }

    void Painter::line(glm::vec2 p0, glm::vec2 p1,
                       float width, glm::vec4 color) const {
#if 0
        log(logging::excessive,
            "drawLine called with: "s +
            to_string(p0) + " "s +
            to_string(p1) + " "s +
            std::to_string(width) + " "s +
            to_string(color));
#endif

        const ShaderRegistry &registry = context.getShaderRegistry();

        glUseProgram(registry.getProgram(shaderLine));

        glUniform4f(registry.getUniform(shaderLine, "color"),
                    color.r, color.g, color.b, color.a);

        drawLineGeometry(p0, p1, width, shaderLine);
    }

    void Painter::sinusoidStraight(
        glm::vec2 p0, glm::vec2 p1, int order,
        float width, glm::vec4 color,
        float time, float freq, float lambda, float phase,
        float strokeWidth, float strokeBlur) const {
        const ShaderRegistry &registry = context.getShaderRegistry();

        glUseProgram(registry.getProgram(shaderSinusoid));

        glUniform1i(registry.getUniform(shaderSinusoid, "mode"), 0);
        glUniform1i(registry.getUniform(shaderSinusoid, "order"), order);

        glUniform1f(registry.getUniform(shaderSinusoid, "time"), time);
        glUniform1f(registry.getUniform(shaderSinusoid, "freq"), freq);
        glUniform1f(registry.getUniform(shaderSinusoid, "phase"), freq);
        glUniform1f(registry.getUniform(shaderSinusoid, "lambda"), lambda);

        glUniform1f(
            registry.getUniform(shaderSinusoid, "stroke_width"), strokeWidth);
        glUniform1f(
            registry.getUniform(shaderSinusoid, "stroke_blur"), strokeBlur);

        glUniform4f(registry.getUniform(shaderSinusoid, "color"),
                    color.r, color.g, color.b, color.a);

        drawLineGeometry(p0, p1, width, shaderSinusoid);
    }

    void Painter::sinusoidCircular(
        glm::vec2 center, int order,
        float width, float height, glm::vec4 color,
        float time, float freq, float lambda, float phase,
        float strokeWidth, float strokeBlur) const {
        const ShaderRegistry &registry = context.getShaderRegistry();

        glUseProgram(registry.getProgram(shaderSinusoid));

        glUniform1i(registry.getUniform(shaderSinusoid, "mode"), 1);
        glUniform1i(registry.getUniform(shaderSinusoid, "order"), order);

        glUniform1f(registry.getUniform(shaderSinusoid, "time"), time);
        glUniform1f(registry.getUniform(shaderSinusoid, "freq"), freq);
        glUniform1f(registry.getUniform(shaderSinusoid, "lambda"), lambda);
        glUniform1f(registry.getUniform(shaderSinusoid, "phase"), freq);

        glUniform1f(
            registry.getUniform(shaderSinusoid, "stroke_width"), strokeWidth);
        glUniform1f(
            registry.getUniform(shaderSinusoid, "stroke_blur"), strokeBlur);

        glUniform4f(registry.getUniform(shaderSinusoid, "color"),
                    color.r, color.g, color.b, color.a);

        drawCircleGeometry(center, width, height, shaderSinusoid);
    }

    void Painter::parallels(
        glm::vec2 centerp0, glm::vec2 centerp1,
        int leftRepeat, int rightRepeat,
        std::function<float(int)> funcWidth,
        std::function<float(int)> funcDistance,
        std::function<glm::vec4(int)>  funcColor,
        bool normalizedInput) const {

        // draw center line
        // drawLine(
        //     centerp0, centerp1,
        //     funcWidth(0), funcColor(0)
        //     );

        // vector pointing from p0 -> p1
        glm::vec2 diff = centerp1 - centerp0;

        // rotate left/right
        glm::vec2 left  = glm::normalize(glm::vec2(-diff.y, diff.x));
        glm::vec2 right = -left;

        // create pairs of directions and repeats
        std::vector<std::pair<glm::vec2, int>> direction_repeat;
        direction_repeat.push_back(std::make_pair(left,  leftRepeat));
        direction_repeat.push_back(std::make_pair(right, rightRepeat));

        // intermediate line endpoints
        glm::vec2 repeatp0;
        glm::vec2 repeatp1;

        const Rect & viewport = context.getViewport2D();

        // draw lines in each 'direction
        for(auto &dr : direction_repeat) {
            repeatp0 = centerp0;
            repeatp1 = centerp1;
            // 'repeat times
            for(int r = 0 ; r < dr.second ; ++r) {
                repeatp0 += dr.first * funcDistance(r);
                repeatp1 += dr.first * funcDistance(r);

                glm::vec2 p0 = repeatp0;
                glm::vec2 p1 = repeatp1;

                if(normalizedInput) {
                    p0 = denormalize(p0, viewport);
                    p1 = denormalize(p1, viewport);
                }
                line(p0, p1, funcWidth(r), funcColor(r));
            }
        }
    }

    void Painter::drawLineGeometry(glm::vec2 p0, glm::vec2 p1,
                                   float width, std::string shader) const {
        glm::vec2 line = p1 - p0;

        glm::mat4 model;
        model = glm::translate(model, glm::vec3{p0[0], p0[1], 0.f});
        model = glm::rotate(model, std::atan2(line[1], line[0]),
                            glm::vec3{0, 0, 1});
        model = glm::scale(model,
                           glm::vec3(glm::length(line), width, 1));
        model = glm::translate(model, glm::vec3{0.5f, 0.f, 0.f});

        glm::mat4 proj = context.getProjection2D();
        glm::mat4 mvp = proj * model;

        glUniformMatrix4fv(
            context.getShaderRegistry().getUniform(shader, "mvp"),
            1, GLboolean(false), glm::value_ptr(mvp));

        quad.draw();
    }

    void Painter::drawCircleGeometry(glm::vec2 center, float width, float height,
                                     std::string shader) const {
        glm::mat4 model;
        model = glm::translate(model, glm::vec3{center[0], center[1], 0.f});
        model = glm::scale(model, glm::vec3(width, height, 1.0f));

        glm::mat4 proj = context.getProjection2D();
        glm::mat4 mvp = proj * model;

        glUniformMatrix4fv(
            context.getShaderRegistry().getUniform(shader, "mvp"),
            1, GLboolean(false), glm::value_ptr(mvp));

        quad.draw();
    }
}
