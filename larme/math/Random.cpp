#include "Random.hpp"

namespace larme {
namespace math {
        
int Random::between(const int a, const int b) {
    int min = std::min(a, b);
    int max = std::max(a, b);
    int diff = (max - min) + 1;
    return static_cast<int>(arc4random_uniform(diff)) + min;
}
    
int Random::oneOrMinusOne() {
    return between(0, 1) ? 1 : -1;
}

}
}
