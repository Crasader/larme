#pragma once

#include <bitset>

namespace larme{
namespace templates{

template<int N> class FlagManager
{
public:
    FlagManager() {
        
    }
    FlagManager(std::string flagString):
    flagBits(flagString) {
    }
    bool get(int flagNumber) {
        return flagBits.at(flagNumber);
    }
    void set(int flagNumber, bool flag) {
        flagBits[flagNumber] = flag;
    }
    std::string toString() {
        return flagBits.to_string();
    }
private:
    std::bitset<N> flagBits;
};

} // namespace templates
} // namespace larme