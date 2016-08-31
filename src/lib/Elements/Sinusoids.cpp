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

#include <glbinding/gl/gl.h>

#include <glm/vec2.hpp>
#include <glm/gtc/constants.hpp>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>

#include <Graphics/Geometry/Transforms.hpp>
#include <Graphics/Painter.hpp>

#include "Sinusoids.hpp"

namespace etudes {

    using namespace gl;
    using logging::LogLevel;

    std::map<std::string, Sinusoids::DrawMode> mapDrawMode {
        {"straight", Sinusoids::STRAIGHT},
        {"mirrored", Sinusoids::MIRRORED},
        {"circular", Sinusoids::CIRCULAR},
    };

    std::map<std::string, Sinusoids::OffsetMode> mapOffsetMode {
        {"absolute", Sinusoids::ABSOLUTE},
        {"increment", Sinusoids::INCREMENT},
        {"increment-falloff", Sinusoids::INCREMENT_FALLOFF},
    };

    void Sinusoids::registerInputs() {
        registerInput("amplitudes", vec_float_t{1.0f});
        registerInput("draw-mode", vec_string_t{"circular"});

        registerInput("center", vec_float_t{0.5f, 0.5f});

        registerInput("width", vec_float_t{0.1});
        registerInput("width-amp", vec_float_t{0.0});

        registerInput("freq", vec_float_t{1.0f});
        registerInput("freq-amp", vec_float_t{0.0f});
        registerInput("lambda", vec_float_t{1.0f});
        registerInput("lambda-amp", vec_float_t{0.0f});
        registerInput("phase-amp", vec_float_t{0.0f});

        registerInput("circle-width", vec_float_t{0.5f});

        registerInput("stroke-width", vec_float_t{0.5f});
        registerInput("stroke-blur", vec_float_t{0.0f});

        registerInput("offset-mode", vec_string_t{"absolute"});
        registerInput("offset-scale", vec_float_t{1.0f});

        registerInput("color", vec_float_t{1.0f, 1.0f, 1.0f, 1.0f});
        registerInput("color-amp",  vec_float_t{0.0f, 0.0f, 0.0f, 0.0f});
    }

    void Sinusoids::update() {
        amplitudes = getValue<vec_float_t>("amplitudes");
        offsets = calculateOffsets(offsetMode, amplitudes);

        center = getValue<glm::vec2>("center");

        widthBase = getValue<float>("width");
        widthAmp = getValue<float>("width-amp");

        colorBase = getValue<glm::vec4>("color");
        colorAmp = getValue<glm::vec4>("color-amp");

        freq = getValue<float>("freq");

        freqAmp = getValue<float>("freq-amp");
        phaseAmp = getValue<float>("phase-amp");

        lambda = getValue<float>("lambda");
        lambdaAmp = getValue<float>("lambda-amp");

        circleWidth = getValue<float>("circle-width");

        strokeWidth = getValue<float>("stroke-width");
        strokeBlur = getValue<float>("stroke-blur");

        drawMode = mapDrawMode[getValue<std::string>("draw-mode")];
        offsetMode = mapOffsetMode[getValue<std::string>("offset-mode")];

        integratePhases(amplitudes);
    }

    void
    Sinusoids::integratePhases(const std::vector<float> &amplitudes)
    {
        phases.resize(amplitudes.size());
        phasesCircular.resize(amplitudes.size());

        float time = util::seconds();
        float deltaT = time - timeLast;
        timeLast = time;

        float PI = glm::pi<float>();
        for(size_t index = 0 ; index < amplitudes.size() ; ++index) {
            phases[index] +=
                deltaT * 2 * PI * (freq + freqAmp * amplitudes[index]);
            phases[index] =
                std::fmod(phases[index], 2 * PI);

            phasesCircular[index] +=
                deltaT * 2 * PI * (lambda + lambdaAmp * amplitudes[index]);
            phasesCircular[index] =
                std::fmod(phasesCircular[index], 2 * PI);
        }
    }

    void Sinusoids::draw() {

        for(int index = amplitudes.size()-1 ; index >= 0 ; index--) {
            float amplitude = amplitudes[index];

            colorDraw = colorBase + colorAmp * amplitude;
            phaseDraw = phases[index] + phaseAmp * amplitude;
            phaseCircularDraw = phasesCircular[index];

            switch(drawMode) {
            case STRAIGHT:
                drawSinusoidStraight(index);
                break;

            case MIRRORED:
                drawSinusoidMirrored(index);
                break;

            case CIRCULAR:
                drawSinusoidCircular(index);
                break;
            }
        }
    }

    std::vector<float>
    Sinusoids::calculateOffsets(OffsetMode offsetMode,
                                const std::vector<float> &amplitudes) {
        std::vector<float> offsets;
        offsets.resize(amplitudes.size());

        float offset = 0.f;
        float offsetScale = getValue<float>("offset-scale");

        for(size_t index = 0 ; index < amplitudes.size() ; ++index) {
            float amplitude = amplitudes[index];

            switch(offsetMode) {
            case ABSOLUTE:
                offset = float(index+1) / float(amplitudes.size()) / 2.f;
                break;
            case INCREMENT:
                offset += amplitude;
                break;
            case INCREMENT_FALLOFF:
                offset += amplitude / float(index+1);
                break;
            }

            offsets[index] = offset * offsetScale;
        }

        return offsets;
    }

    void Sinusoids::drawSinusoidStraight(int index) {

        const Rect &viewport = getContext().getViewport2D();
        glm::vec2 start, end;

        float yStart = 0.f;
        float yEnd = 1.f;

        widthDraw = viewport.getDiagonal() / 2.0f *
            (widthBase + widthAmp * amplitudes[index]);

        start = glm::vec2(center[0] + offsets[index], yStart);
        end = glm::vec2(center[0] + offsets[index], yEnd);
        start = denormalize(start, viewport);
        end = denormalize(end, viewport);

        getPainter().setColor(colorDraw);
        getPainter().sinusoidStraight(
            start, end, index+1, widthDraw,
            lambda, phaseDraw + 0.0f,
            strokeWidth, strokeBlur);
    }

    void Sinusoids::drawSinusoidMirrored(int index) {
        Painter & painter = getPainter();
        const Rect &viewport = getContext().getViewport2D();

        glm::vec2 start, end;

        float yStart = 0.f;
        float yEnd = 1.f;

        widthDraw = viewport.getDiagonal() / 2.0f *
            (widthBase + widthAmp * amplitudes[index]);

        start = glm::vec2(center[0] + offsets[index], yStart);
        end = glm::vec2(center[0] + offsets[index], yEnd);
        start = denormalize(start, viewport);
        end = denormalize(end, viewport);

        painter.setColor(colorDraw);

        painter.sinusoidStraight(
            start, end, index+1, widthDraw,
            lambda, phaseDraw + 0.0f,
            strokeWidth, strokeBlur);

        start = glm::vec2(center[0] - offsets[index], yStart);
        end = glm::vec2(center[0] - offsets[index], yEnd);
        start = denormalize(start, viewport);
        end = denormalize(end, viewport);

        painter.sinusoidStraight(
            start, end, index+1, widthDraw,
            lambda, phaseDraw + glm::pi<float>(),
            strokeWidth, strokeBlur);
    }

    void Sinusoids::drawSinusoidCircular(int index) {
        Painter & painter = getPainter();
        const Rect &viewport = getContext().getViewport2D();

        widthDraw = viewport.getDiagonal() / 2.0f *
            (widthBase + widthAmp * amplitudes[index] +
             offsets[index]);

        painter.setColor(colorDraw);
        painter.sinusoidCircular(
            denormalize(center, viewport), index+1,
            widthDraw, widthDraw,
            lambda, phaseDraw, phaseCircularDraw,
            circleWidth, strokeWidth, strokeBlur);
    }
}
