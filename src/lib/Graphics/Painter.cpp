/*

  Études Audiovisuels - Graphical elements for audiovisual composition.
  Copyright (C) 2015-2016 Patric Schmitz

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

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

    const std::string shaderLine = "solid";
    const std::string shaderRect = "solid";
    const std::string shaderSinusoid = "sinusoid";

    Painter::Painter() {
        util::registerDefaultShaders(shaders);

        programLine = shaders.getProgram(shaderLine);
        uniformLineColor = shaders.getUniform(shaderLine, "color");

        programRect = shaders.getProgram(shaderRect);
        uniformRectColor = shaders.getUniform(shaderRect, "color");
        uniformRectMVP = shaders.getUniform(shaderRect, "mvp");

        shaders.registerShader("sinusoid", GL_FRAGMENT_SHADER,
                               {"resources/shaders/elements/sinusoid.frag"});

        programSinusoid =
            shaders.registerProgram("sinusoid", {"mvp-uv", "sinusoid"});

        shaders.registerUniform("sinusoid", "mvp");

        uniformSinusoidMode   = shaders.registerUniform("sinusoid", "mode");
        uniformSinusoidOrder  = shaders.registerUniform("sinusoid", "order");

        uniformSinusoidTime   = shaders.registerUniform("sinusoid", "time");
        uniformSinusoidFreq   = shaders.registerUniform("sinusoid", "freq");
        uniformSinusoidPhase  = shaders.registerUniform("sinusoid", "phase");
        uniformSinusoidLambda = shaders.registerUniform("sinusoid", "lambda");

        uniformSinusoidCircleWidth = shaders.registerUniform("sinusoid",
                                                             "circleWidth");
        uniformSinusoidStrokeWidth = shaders.registerUniform("sinusoid",
                                                             "strokeWidth");
        uniformSinusoidStrokeBlur = shaders.registerUniform("sinusoid",
                                                            "strokeBlur");

        uniformSinusoidColor = shaders.registerUniform("sinusoid", "color");

        reset();
    }

    void Painter::reset() {
        setInputNormalized(true);
        setColor({1, 1, 1, 1});
    }

    void Painter::setContext(const Context & context) {
        this->context = &context;
    }

    void Painter::setColor(glm::vec4 color) {
        this->color = color;
    }

    void Painter::setInputNormalized(bool normalized) {
        normalizedInput = normalized;
    }

    void Painter::line(glm::vec2 p0, glm::vec2 p1, float width) {
#if 0
        log(logging::excessive,
            "drawLine called with: "s +
            to_string(p0) + " "s +
            to_string(p1) + " "s +
            std::to_string(width) + " "s +
            to_string(color));
#endif
        assert(context);

        glUseProgram(programLine);
        glUniform4f(uniformLineColor,
                    color.r, color.g, color.b, color.a);

        const Rect & viewport = context->getViewport2D();
        if(normalizedInput) {
            p0 = denormalize(p0, viewport);
            p1 = denormalize(p1, viewport);
        }

        drawLineGeometry(p0, p1, width, shaderLine);
    }

    void Painter::rect(glm::vec2 topLeft, glm::vec2 bottomRight) {
        assert(context);

        glUseProgram(programRect);
        glUniform4f(uniformRectColor, color.r, color.g, color.b, color.a);

        const Rect & viewport = context->getViewport2D();
        if(normalizedInput) {
            topLeft = denormalize(topLeft, viewport);
            bottomRight = denormalize(bottomRight, viewport);
        }

        auto diag = bottomRight - topLeft;

        glm::mat4 model;
        model = glm::translate(model, glm::vec3(topLeft[0], topLeft[1], 0));
        model = glm::scale(model, glm::vec3(diag[0], diag[1], 1));
        model = glm::translate(model, glm::vec3(0.5, 0.5, 0));

        // EDB(model);

        glm::mat4 proj = context->getProjection2D();
        glm::mat4 mvp = proj * model;
        glUniformMatrix4fv(
            uniformRectMVP,
            1, GLboolean(false), glm::value_ptr(mvp));

        quad.draw();
    }

    void Painter::rect(glm::vec2 center, float size) {
        glm::vec2 topLeft = {center[0] - size, center[1] + size};
        glm::vec2 bottomRight = {center[0] + size, center[1] - size};
        rect(topLeft, bottomRight);
    }

    void Painter::sinusoidStraight(
        glm::vec2 p0, glm::vec2 p1, int order, float width,
        float time, float freq, float lambda, float phase,
        float strokeWidth, float strokeBlur) const {

        glUseProgram(shaders.getProgram(shaderSinusoid));

        glUniform1i(uniformSinusoidMode, 0);
        glUniform1i(uniformSinusoidOrder, order);

        glUniform1f(uniformSinusoidTime, time);
        glUniform1f(uniformSinusoidFreq, freq);
        glUniform1f(uniformSinusoidPhase, phase);
        glUniform1f(uniformSinusoidLambda, lambda);

        glUniform1f(uniformSinusoidStrokeWidth, strokeWidth);
        glUniform1f(uniformSinusoidStrokeBlur, strokeBlur);

        glUniform4f(uniformSinusoidColor, color.r, color.g, color.b, color.a);

        drawLineGeometry(p0, p1, width, shaderSinusoid);
    }

    void Painter::sinusoidCircular(
        glm::vec2 center, int order, float width, float height,
        float time, float freq, float lambda, float phase,
        float circleWidth, float strokeWidth, float strokeBlur) const {

        glUseProgram(shaders.getProgram(shaderSinusoid));

        glUniform1i(uniformSinusoidMode, 1);
        glUniform1i(uniformSinusoidOrder, order);

        glUniform1f(uniformSinusoidTime, time);
        glUniform1f(uniformSinusoidFreq, freq);
        glUniform1f(uniformSinusoidLambda, lambda);
        glUniform1f(uniformSinusoidFreq, freq);

        glUniform1f(uniformSinusoidCircleWidth, circleWidth);
        glUniform1f(uniformSinusoidStrokeWidth, strokeWidth);
        glUniform1f(uniformSinusoidStrokeBlur, strokeBlur);

        glUniform4f(uniformSinusoidColor, color.r, color.g, color.b, color.a);

        drawCircleGeometry(center, width, height, shaderSinusoid);
    }

    void Painter::parallels(
        glm::vec2 centerp0, glm::vec2 centerp1,
        int leftRepeat, int rightRepeat,
        std::function<float(int)> funcWidth,
        std::function<float(int)> funcDistance,
        std::function<glm::vec4(int)>  funcColor) {

        // draw center line
        setColor(funcColor(0));
        line(centerp0, centerp1, funcWidth(0));

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

                setColor(funcColor(r));
                line(p0, p1, funcWidth(r));
            }
        }
    }

    void Painter::drawLineGeometry(glm::vec2 p0, glm::vec2 p1,
                                   float width, std::string shader) const {
        assert(context);

        glm::vec2 line = p1 - p0;

        glm::mat4 model;
        model = glm::translate(model, glm::vec3{p0[0], p0[1], 0.f});
        model = glm::rotate(model, std::atan2(line[1], line[0]),
                            glm::vec3{0, 0, 1});
        model = glm::scale(model,
                           glm::vec3(glm::length(line), width, 1));
        model = glm::translate(model, glm::vec3{0.5f, 0.f, 0.f});

        glm::mat4 proj = context->getProjection2D();
        glm::mat4 mvp = proj * model;

        glUniformMatrix4fv(shaders.getUniform(shader, "mvp"),
                           1, GLboolean(false), glm::value_ptr(mvp));

        quad.draw();
    }

    void Painter::drawCircleGeometry(glm::vec2 center, float width, float height,
                                     std::string shader) const {
        assert(context);

        glm::mat4 model;
        model = glm::translate(model, glm::vec3{center[0], center[1], 0.f});
        model = glm::scale(model, glm::vec3(width, height, 1.0f));

        glm::mat4 proj = context->getProjection2D();
        glm::mat4 mvp = proj * model;

        glUniformMatrix4fv(shaders.getUniform(shader, "mvp"),
                           1, GLboolean(false), glm::value_ptr(mvp));

        quad.draw();
    }
}
