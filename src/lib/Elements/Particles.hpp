#ifndef ETUDES_PARTICLES
#define ETUDES_PARTICLES

#include <Receivers/Element.hpp>

namespace etudes {
    class Particles : public Element {
    public:
        void registerInputs() override;
        void draw() override;

    private:
    };
}

#endif // ETUDES_PARTICLES
