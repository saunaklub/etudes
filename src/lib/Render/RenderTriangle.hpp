#ifndef _ETUDES_RENDERTRIANGLE
#define _ETUDES_RENDERTRIANGLE

#include "Render.hpp"

namespace etudes {
    class RenderTriangle : public Render {
    public:
        RenderTriangle() {};
        virtual ~RenderTriangle() {};
        
        void render();

    private:
    };
}

#endif // _ETUDES_RENDERTRIANGLE
