#ifndef _ETUDES_RENDERTEMPLATE
#define _ETUDES_RENDERTEMPLATE

#include "../Renderer.hpp"

namespace etudes {
    class RenderTemplate : public Renderer {
    public:
        RenderTemplate() {};
        virtual ~RenderTemplate() {};
        
        std::string name() override;
        void render() override;

    private:
    };
}

#endif // _ETUDES_RENDERTEMPLATE
