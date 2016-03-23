#pragma once

#include <iostream>

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;

namespace larme {
namespace ui {

class Text
{
public:
    
    static void setCallBackTo(cocos2d::Node* targetNode, const char* buttonName, const std::function<void()> &callback);
    static void replaceText(cocos2d::Node* targetNode, const char* nameNodeText, const std::string &string);
    
};

}// namespace ui
}// namespace larme