#ifndef _ETUDES_TEMPLATERENDERER
#define _ETUDES_TEMPLATERENDERER

#include "../Renderer.hpp"

namespace etudes {
    class TemplateRenderer : public Renderer {
    public:
        TemplateRenderer() {};
        virtual ~TemplateRenderer() {};
        
        void render();

    private:
    };
}

#endif // _ETUDES_TEMPLATERENDERER
