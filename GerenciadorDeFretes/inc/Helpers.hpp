#ifndef _HELPERS_HPP_
#define _HELPERS_HPP_

#include <ctime>
#include <cstdlib>

namespace Helpers {
    template<typename T>
    T min(T x, T y)
    {
        return x < y ? x : y;
    }

    template<typename T>
    T max(T x, T y)
    {
        return x > y ? x : y;
    }
}

#endif