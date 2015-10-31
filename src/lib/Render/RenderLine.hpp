#ifndef _ETUDES_LINERENDER
#define _ETUDES_LINERENDER

#include "Render.hpp"

namespace etudes {
    class LineRender : public Render {
    public:
        LineRender() {};
        virtual ~LineRender() {};
        
        void render();

    private:
    };
}

#endif // _ETUDES_LINERENDER
