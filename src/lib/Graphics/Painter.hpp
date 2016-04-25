#ifndef ETUDES_PAINTER
#define ETUDES_PAINTER

#include <glbinding/gl/gl.h>
#include <glm/glm.hpp>

#include <Graphics/Quad.hpp>

namespace etudes {
    class Context;
    class Painter {
    public:
        Painter(const Context &context);

        void init();

        void line(glm::vec2 p0, glm::vec2 p1,
                  float width, glm::vec4 color) const;

        void sinusoid(glm::vec2 p0, glm::vec2 p1,
                      float width, glm::vec4 color) const;

        void parallels(
            glm::vec2 centerp0, glm::vec2 centerp1,
            int leftRepeat, int rightRepeat,
            std::function<float(int)> funcWidth,
            std::function<float(int)> funcDistance,
            std::function<glm::vec4(int)> funcColor,
            bool normalizedInput=false) const;

    private:
        void drawLineGeometry(glm::vec2 p0, glm::vec2 p1,
                              float width) const;

        const Context &context;
        Quad quad;
    };
}

#endif // ETUDES_PAINTER
