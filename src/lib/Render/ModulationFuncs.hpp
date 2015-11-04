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

#include <functional>
#include <cmath>

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
    function<T(int)> funcSin(T t, float a, float omega, float phi=0) {
        return [=](int k) {
            return t + a*sin(k*omega + phi);
        };
    }
}

#endif
