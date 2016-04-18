#include <glm/gtc/constants.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <Utility/ModulationFuncs.hpp>

#include <Graphics/Context.hpp>

#include "Lines.hpp"

namespace etudes {
    using glm::pi;
    using glm::vec2;
    using glm::vec4;

    void Lines::registerInputs() {
        registerInput("/count", {100.0f});
        registerInput("/angle", {pi<float>()/2.0f});

        registerInput("/distance/base",      {0.1f});
        registerInput("/distance/amplitude", {0.0f});
        registerInput("/distance/omega",     {0.0f});
        registerInput("/distance/lambda",    {0.0f});
        registerInput("/width/base",      {5.0f});
        registerInput("/width/amplitude", {0.0f});
        registerInput("/width/omega",     {0.0f});
        registerInput("/width/lambda",    {0.0f});
        registerInput("/color/base",      {1.0f, 1.0f, 1.0f, 1.0f});
        registerInput("/color/amplitude", {0.0f, 0.0f, 0.0f, 0.0f});
        registerInput("/color/omega",     {0.0f});
        registerInput("/color/lambda",    {0.0f});
    }

    void Lines::draw(const Context &context) {
        auto dist_b = getValue<float>("/distance/base");
        auto dist_a = getValue<float>("/distance/amplitude");
        auto dist_o = getValue<float>("/distance/omega");
        auto dist_l = getValue<float>("/distance/lambda");

        auto width_b = getValue<float>("/width/base");
        auto width_a = getValue<float>("/width/amplitude");
        auto width_o = getValue<float>("/width/omega");
        auto width_l = getValue<float>("/width/lambda");

        auto color_b = getValue<vec4>("/color/base");
        auto color_a = getValue<vec4>("/color/amplitude");
        auto color_o = getValue<float>("/color/omega");
        auto color_l = getValue<float>("/color/lambda");

        auto dist  = funcSin(dist_b, dist_a, dist_o, dist_l);
        auto width = funcSin(width_b, width_a, width_o, width_l);
        auto color = funcSin(color_b, color_a, color_o, color_l);

        auto count = getValue<float>("/count");
        auto angle = getValue<float>("/angle");

        auto p0 = vec2(2.0f*cos(angle),
                       2.0f*sin(angle));
        auto p1 = -p0;

        context.drawParallels(p0, p1,
                              count, count,
                              width, dist, color);
    }
}
