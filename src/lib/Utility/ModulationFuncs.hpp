/*

  Études Audiovisuel - Graphical elements for audiovisual composition.
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

#ifndef MODULATION_FUNCS
#define MODULATION_FUNCS

#include <cmath>
#include <glm/gtc/constants.hpp>
#include <glm/vec3.hpp>

#include <functional>
#include <iostream>

#include <Utility/Utility.hpp>

namespace etudes {
    using std::function;
    using std::sin;

    using util::seconds;

    template<class T>
        function<T(float)> funcConst(T t) {
            return [=](float) {
                return t;
            };
        }

    /**
     * Generic sinusoidal modulation function. Maps a real-valued
     * position or index to a sin function oscillating in space and
     * time, think wave equation.
     *
     * @param base Base value around which it oscillation occurs.
     * @param amp Amplitude of the oscillation.
     * @param omega Time frequency (Hz).
     * @param lambda Space frequency ("1/position").
     * @param phi Initial phase.
     */
    template<class T>
        function<T(float)> funcSin(
                T base, T amp,
                float omega, float lambda=0,
                float phi=0) {

            return [=](float k) {
                return base + amp*sinf(
                    2.0f*glm::pi<float>()
                    * (k*lambda + util::seconds()*omega)
                    + phi);
            };
        }
}

#endif
