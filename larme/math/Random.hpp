#pragma once

#include "cocos2d.h"

USING_NS_CC;

namespace larme {
namespace math {

class Random
{
public:
    static int between(const int min, const int max);
};

}
}