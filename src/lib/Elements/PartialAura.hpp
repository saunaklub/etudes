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
        void update();
        void draw(const Context &context,
                  const Painter &painter);

    private:
        std::vector<float>
        calculateOffsets(OffsetMode offsetMode,
                         const std::vector<float> &partials);

        void drawSinusoidStraight(
            int index, const Context &context, const Painter &painter);
        void drawSinusoidCircular(
            int index, const Context &context, const Painter &painter);

        vec_float_t amplitudes;
        vec_float_t offsets;

        glm::vec2 center;

        float widthBase;
        float widthAmp;
        float widthDraw;

        glm::vec4 colorBase;
        glm::vec4 colorAmp;
        glm::vec4 colorDraw;

        float time;
        float freq;
        float lambda;

        float phaseBase;
        float phaseAmp;
        float phaseDraw;

        float strokeWidth;
        float strokeBlur;

        DrawMode drawMode;
        OffsetMode offsetMode;
    };

}

#endif // ETUDES_PARTIALAURA
