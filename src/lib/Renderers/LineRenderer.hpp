#ifndef _ETUDES_LINERENDERER
#define _ETUDES_LINERENDERER

#include "../Renderer.hpp"

namespace etudes {
    class LineRenderer : public Renderer {
    public:
        LineRenderer() {};
        virtual ~LineRenderer() {};
        
        void render();

    private:
    };
}

#endif // _ETUDES_LINERENDERER
