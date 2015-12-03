/*

Études Audiovisuel - graphical elements for audiovisual composition
Copyright (C) 2015 Patric Schmitz, Claudio Cabral

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

#ifndef _MODULATION_FUNCS
#define _MODULATION_FUNCS

#include <cmath>

#include <functional>
#include <chrono>
#include <iostream>

namespace {
    std::chrono::high_resolution_clock modClock;
    std::chrono::high_resolution_clock::time_point t0 = modClock.now();

    long microSeconds() {
        std::chrono::duration_cast<std::chrono::microseconds>
            (modClock.now() - t0);
    }

    double seconds() {
        return microSeconds() / 1000000.0;
    }
}

namespace etudes {
    using std::function;
    using std::sin;

    template<class T>
    function<T(int)> funcConst(T t) {
        return [=](int) {
            return t;
        };
    }

    template<class T>
    function<T(int)> funcSinK(T base, float amp,
                             float omega, float phi=0) {
        return [=](int k) {
            return base + amp*sin(k*omega + phi);
        };
    }

    template<class T>
    function<T(int)> funcSinT(T base, T amp,
                              float omega,
                              float phi=0) {
        return [=](int k) {
            double t = seconds();
            return base + amp*sin(omega*t + phi);
        };
    }
}



#endif
