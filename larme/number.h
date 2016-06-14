#pragma once

namespace larme {
namespace number {
    
    template<typename T>
    T fit(const T min, const T value, const T max)
    {
        if(value < min)
            return min;
        if(value > max)
            return max;
        return value;
    }
    constexpr int sign(const int v) {
        return ((v >> std::numeric_limits<int>::digits) << 1) + 1;
    }
    constexpr int sign(const double v) { return (v > 0) - (v < 0); }
    constexpr int sign(const float v) { return (v > 0) - (v < 0); }
}
}
