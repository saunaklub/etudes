#ifndef _ETUDES_RENDERLINE
#define _ETUDES_RENDERLINE

#include "Render.hpp"

namespace etudes {
    class RenderLine : public Render {
    public:
        RenderLine() {};
        virtual ~RenderLine() {};
        
        std::string name() override;
        void render() override;

    private:
    };
}

#endif // _ETUDES_RENDERLINE
