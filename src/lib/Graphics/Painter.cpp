/*

  Études Audiovisuelles - Graphical elements for audiovisual composition.
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

#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glow/common/str_utils.hh>
#include <glow/objects/Program.hh>
#include <glow/objects/Shader.hh>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>

#include <Graphics/Context.hpp>
#include <Graphics/Geometry/Transforms.hpp>

#include "Painter.hpp"

namespace etudes {

    using logging::LogLevel;

    const std::string shaderLine = "solid";
    const std::string shaderSinusoid = "sinusoid";

    Painter::Painter() {
        util::registerDefaultShaders(shaders);

        programSolid = glow::Program::createFromFiles(
            {"resources/shaders/mvp-uv.vsh",
             "resources/shaders/solid-color.fsh"});
        programSinusoid = glow::Program::createFromFiles(
            {"resources/shaders/mvp-uv.vsh",
             "resources/shaders/elements/sinusoid.fsh"});

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

    void Painter::drawLine(glm::vec2 p0, glm::vec2 p1, float width) {
#if 0
        log(logging::excessive,
            "drawLine called with: "s +
            to_string(p0) + " "s +
            to_string(p1) + " "s +
            std::to_string(width) + " "s +
            to_string(color));
#endif
        assert(context);

        auto shader = programSolid->use();
        shader.setUniform("color", color);

        const Rect & viewport = context->getViewport2D();
        if(normalizedInput) {
            p0 = denormalize(p0, viewport);
            p1 = denormalize(p1, viewport);
        }

        drawLineGeometry(p0, p1, width, shader);
    }

    void Painter::drawLineGeometry(glm::vec2 p0, glm::vec2 p1, float width,
                                   glow::UsedProgram &shader) const {
        assert(context);

        glm::vec2 line = p1 - p0;

        auto model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3{p0[0], p0[1], 0.f});
        model = glm::rotate(model, std::atan2(line[1], line[0]),
                            glm::vec3{0, 0, 1});
        model = glm::scale(model,
                           glm::vec3(glm::length(line), width, 1));
        model = glm::translate(model, glm::vec3{0.5f, 0.f, 0.f});

        glm::mat4 proj = context->getProjection2D();
        glm::mat4 mvp = proj * model;

        shader.setUniform("mvp", mvp);

        quad.draw();
    }

    void Painter::drawRect(Rect rect) {
        drawRect(glm::vec2(rect.getX(), rect.getY() + rect.getHeight()),
             glm::vec2(rect.getX() + rect.getWidth(), rect.getY()));
    }

    void Painter::drawRect(glm::vec2 center, float size) {
        glm::vec2 topLeft = {center[0] - size, center[1] + size};
        glm::vec2 bottomRight = {center[0] + size, center[1] - size};
        drawRect(topLeft, bottomRight);
    }

    void Painter::drawRect(glm::vec2 topLeft, glm::vec2 bottomRight) {
        assert(context);

        Rect viewport = context->getViewport2D();
        if(normalizedInput) {
            topLeft = denormalize(topLeft, viewport);
            bottomRight = denormalize(bottomRight, viewport);
        }

        auto model = glm::mat4(1.f);
        auto diag = bottomRight - topLeft;

        model = glm::translate(model, glm::vec3(topLeft[0], topLeft[1], 0));
        model = glm::scale(model, glm::vec3(diag[0], diag[1], 1));
        model = glm::translate(model, glm::vec3(0.5, 0.5, 0));

        glm::mat4 proj = context->getProjection2D();
        glm::mat4 mvp = proj * model;

        auto shader = programSolid->use();

        shader.setUniform("mvp", mvp);
        shader.setUniform("color", color);

        quad.draw();
    }

    void Painter::drawSinusoidStraight(
        glm::vec2 p0, glm::vec2 p1, int order, float width,
        float lambda, float phase,
        float strokeWidth, float strokeBlur) const {

        auto shader = programSinusoid->use();

        shader.setUniform("mode", 0);
        shader.setUniform("order", order);

        shader.setUniform("lambda", lambda);
        shader.setUniform("phase", phase);

        shader.setUniform("strokeWidth", strokeWidth);
        shader.setUniform("strokeBlur", strokeBlur);

        shader.setUniform("color", color);

        drawLineGeometry(p0, p1, width, shader);
    }

    void Painter::drawSinusoidCircular(
        glm::vec2 center, int order, float width, float height,
        float lambda, float phase, float phaseCircular,
        float circleWidth, float strokeWidth, float strokeBlur) const {

        auto shader = programSinusoid->use();

        shader.setUniform("mode", 1);
        shader.setUniform("order", order);

        shader.setUniform("lambda", lambda);
        shader.setUniform("phase", phase);
        shader.setUniform("phaseCircular", phaseCircular);

        shader.setUniform("circleWidth", circleWidth);
        shader.setUniform("strokeWidth", strokeWidth);
        shader.setUniform("strokeBlur", strokeBlur);

        shader.setUniform("color", color);

        drawCircleGeometry(center, width, height, shader);
    }

    void Painter::drawParallels(
        glm::vec2 centerp0, glm::vec2 centerp1,
        int leftRepeat, int rightRepeat,
        std::function<float(int)> funcWidth,
        std::function<float(int)> funcDistance,
        std::function<glm::vec4(int)>  funcColor) {

        // draw center line
        setColor(funcColor(0));
        drawLine(centerp0, centerp1, funcWidth(0));

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
                drawLine(p0, p1, funcWidth(r));
            }
        }
    }

    void Painter::drawCircleGeometry(
        glm::vec2 center, float width, float height,
        glow::UsedProgram &shader) const {
        assert(context);

        auto model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3{center[0], center[1], 0.f});
        model = glm::scale(model, glm::vec3(width, height, 1.0f));

        glm::mat4 proj = context->getProjection2D();
        glm::mat4 mvp = proj * model;

        shader.setUniform("mvp", mvp);

        quad.draw();
    }
}
