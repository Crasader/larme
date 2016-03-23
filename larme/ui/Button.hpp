#pragma once

#pragma once

#include <iostream>

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;

namespace larme {
namespace ui {
    
class Button
{
public:
    static void setCallBackTo(cocos2d::Node* targetNode, const char* buttonName, const cocos2d::ui::Widget::ccWidgetTouchCallback &callback);
    static void setCallBackTo(cocos2d::Node* targetNode, const char* buttonName,
                                    const std::function<void()> &callbackBegan);
    
    static void setCallBackTo(cocos2d::Node* targetNode, const char* buttonName,
                                    const std::function<void()> &callbackBegan,
                                    const std::function<void()> &callbackEnd
                                    );
    
    static void setCallBackToLayerd(cocos2d::Node* targetNode, const char* nameNodeButtonLayerd, const char* nameInnerNodeButton, const std::function<void()> &callback);
    
};
    
}// namespace ui
}// namespace larme