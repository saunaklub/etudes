#ifndef _ETUDES_RENDERPRIMITIVES
#define _ETUDES_RENDERPRIMITIVES

#include <functional>

#include <glm/glm.hpp>

namespace etudes {
    using std::function;

    using glm::vec2;
    using glm::vec3;
    
    class RenderPrimitives {
    public:
        void drawLine(vec2 p0, vec2 p1,
                      float width,
                      vec3 color);

        void drawParallels(
            vec2 centerp0, vec2 centerp1,
            int leftRepeat, int rightRepeat,
            function<float(int)> funcWidth,
            function<float(int)> funcDistance,
            function<vec3(int)>  funcColor);
      
    private:
    };
}

#endif // _ETUDES_RENDERPRIMITIVES
