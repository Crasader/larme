#include "Random.hpp"

namespace larme {
namespace math {
        
int Random::between(const int min, const int max) {
    int diff = max - min;
    return static_cast<int>(arc4random_uniform(diff)) + min;
}

}
}