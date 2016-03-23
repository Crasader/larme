#pragma once

#pragma once

#include <iostream>

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;

namespace larme {
namespace ui {
    
class CocosStudio
{
public:
    static Node* loadFromCsb(const char* resourceName);
};
    
}// namespace ui
}// namespace larme