#ifndef _ETUDES_RENDERTEMPLATE
#define _ETUDES_RENDERTEMPLATE

#include "../Renderer.hpp"

namespace etudes {
    class RenderTemplate : public Renderer {
    public:
        RenderTemplate() {};
        virtual ~RenderTemplate() {};
        
        void render();

    private:
    };
}

#endif // _ETUDES_RENDERTEMPLATE
