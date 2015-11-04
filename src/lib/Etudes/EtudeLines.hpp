#ifndef _ETUDES_ETUDELINES
#define _ETUDES_ETUDELINES

#include <Render/RenderPrimitives.hpp>

#include "Etude.hpp"

namespace etudes {
    class EtudeLines : public Etude {
    public:
        EtudeLines() {};
        virtual ~EtudeLines() {};
        
        std::string name() override;
        void draw() override;

    private:
        RenderPrimitives render;
    };
}

#endif // _ETUDES_ETUDELINES
