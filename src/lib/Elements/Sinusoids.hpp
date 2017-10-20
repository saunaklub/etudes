/*

  Études Audiovisuelles - Graphical elements for audiovisual composition.
  Copyright (C) 2015-2016 Patric Schmitz

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef ETUDES_SINUSOIDS
#define ETUDES_SINUSOIDS

#include <Receivers/Element.hpp>

namespace etudes {

    class Sinusoids : public Element {
    public:
        enum class DrawMode {
            straight,
            mirrored,
            circular,
        };

        enum class OffsetMode {
            absolute,
            increment,
            incrementFalloff,
        };

        void registerInputs() override;

        // void init();
        void update() override;
        void draw() override;

    private:
        std::vector<float>
        calculateOffsets(OffsetMode offsetMode,
                         const std::vector<float> &amplitudes);

        void
        integratePhases(const std::vector<float> &amplitudes);

        void drawSinusoidStraight(int index);
        void drawSinusoidMirrored(int index);
        void drawSinusoidCircular(int index);

        vec_float_t amplitudes;
        vec_float_t offsets;
        vec_float_t phases;
        vec_float_t phasesCircular;

        glm::vec2 center;

        float widthBase;
        float widthAmp;

        float widthDraw;

        glm::vec4 colorBase;
        glm::vec4 colorAmp;
        glm::vec4 colorDraw;

        float timeLast;
        float freq;
        float freqAmp;
        float lambda;
        float lambdaAmp;

        float phaseAmp;
        float phaseDraw;
        float phaseCircularDraw;

        float strokeWidth;
        float strokeBlur;

        DrawMode drawMode;
        OffsetMode offsetMode;
    };

}

#endif // ETUDES_SINUSOIDS
