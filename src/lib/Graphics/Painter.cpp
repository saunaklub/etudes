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

    Painter::Painter(const Context &context) :
        context(context) {
    }

    void Painter::init() {
        glGenVertexArrays(1, &vaoLine);
        glBindVertexArray(vaoLine);

        const GLfloat coords[] =  {
            0.f, 0.f, 0.f,
            1.f, 0.f, 0.f
        };
        glGenBuffers(1, &vboLine);
        glBindBuffer(GL_ARRAY_BUFFER, vboLine);
        glBufferData(GL_ARRAY_BUFFER,
                     6 * sizeof(GLfloat),
                     coords, GL_DYNAMIC_DRAW);

        GLint attribPosition =
            glGetAttribLocation(
                context.getShaderRegistry().getProgram("line"), "vertPos");
        glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(attribPosition);
        checkGLError("painter: line vertex attrib");
    }

    void Painter::drawLine(glm::vec2 p0, glm::vec2 p1,
                           float width, glm::vec4 color) const {
#if 0
        log(logging::excessive,
            "drawLine called with: "s +
            to_string(p0) + " "s +
            to_string(p1) + " "s +
            std::to_string(width) + " "s +
            to_string(color));
#endif

        glUseProgram(context.getShaderRegistry().getProgram("line"));
        glBindVertexArray(vaoLine);

        glUniform4f(context.getShaderRegistry().getUniform("line", "color"),
                    color.r, color.g, color.b, color.a);

        glm::vec2 line = p1 - p0;

        glm::mat4 model;
        model = glm::translate(model, glm::vec3{p0[0], p0[1], 0.f});
        model = glm::rotate(model, std::atan2(line[1], line[0]),
                            glm::vec3{0, 0, 1});
        model = glm::scale(model,
                           glm::vec3(glm::length(line), glm::length(line), 1));

        glm::mat4 proj = context.getProjection2D();
        glm::mat4 mvp = proj * model;

        glUniformMatrix4fv(
            context.getShaderRegistry().getUniform("line", "mvp"),
            1, GLboolean(false), glm::value_ptr(mvp));

        glDrawArrays(GL_LINES, 0, 2);
    }

    void Painter::drawParallels(
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
                drawLine(p0, p1,
                         funcWidth(r), funcColor(r));
            }
        }
    }
}
