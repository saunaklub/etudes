#ifndef ETUDES_ELEMENTLINE
#define ETUDES_ELEMENTLINE

#include <Elements/Element.hpp>

namespace etudes {
    class ElementLine : public Element {
    public:
        void registerInputs() override;
        void draw() override;

    private:
    };
}

#endif // ETUDES_ELEMENTLINE
