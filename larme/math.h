#pragma once

namespace larme {
namespace math {
    
    template<typename T>
    T fit(const T min, const T value, const T max)
    {
        if(value < min)
            return min;
        if(value > max)
            return max;
        return value;
    }

    constexpr int sgn(const int v) { return ((v >> std::numeric_limits<int>::digits) << 1) + 1; }
    constexpr int sgn(const double v) { return (v > 0) - (v < 0); }
    constexpr int sgn(const float v) { return (v > 0) - (v < 0); }

}
}