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
