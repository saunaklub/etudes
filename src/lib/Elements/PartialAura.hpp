#ifndef ETUDES_PARTIALAURA
#define ETUDES_PARTIALAURA

#include <Receivers/Element.hpp>

namespace etudes {

    class PartialAura : public Element {
    public:
        enum DrawMode {
            STRAIGHT,
            CIRCULAR,
        };

        enum OffsetMode {
            ABSOLUTE,
            INCREMENT,
            INCREMENT_FALLOFF,
        };

        void registerInputs();

        // void init();
        // void update();
        void draw(const Context &context,
                  const Painter &painter);

    private:
        std::vector<float>
        calculateOffsets(OffsetMode offsetMode,
                         const std::vector<float> &partials);

        void drawSinusoidStraight();
        void drawSinusoidCircular();
    };

}

#endif // ETUDES_PARTIALAURA
