#include "Text.hpp"

#include "ui/cocosGUI.h"

namespace larme {
namespace ui {

void Text::setCallBackTo(cocos2d::Node* targetNode, const char* nodeName, const std::function<void()> &callback) {
    auto node = targetNode->getChildByName<cocos2d::ui::Text*>(nodeName);
    if (nullptr == node) {
        CCLOG("cocos2d::ui::Text* node (name:%s) not found.", nodeName);
        return;
    }
    node->setTouchEnabled(true);
    node->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type){
        if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {return;}
        callback();
    });
}

void Text::replaceText(cocos2d::Node* targetNode, const char* nodeName, const std::string &string) {
    auto node = targetNode->getChildByName<cocos2d::ui::Text*>(nodeName);
    if (nullptr == node) {
        CCLOG("label node (name:%s) not found.", nodeName);
        return;
    }
    //CCLOG("label node (name:%s) set to %s", nodeName, string);
    node->setString(string);
}

}
}