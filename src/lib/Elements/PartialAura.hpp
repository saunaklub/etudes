#ifndef ETUDES_PARTIALAURA
#define ETUDES_PARTIALAURA

#include <Receivers/Element.hpp>

namespace etudes {
    class PartialAura : public Element {
    public:
        void registerInputs();

        // void init();
        // void update();
        void draw(const Context &context,
                  const Painter &painter);

    private:
    };
}

#endif // ETUDES_PARTIALAURA
