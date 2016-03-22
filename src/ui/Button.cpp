#include "Button.hpp"

namespace larme {
namespace ui {

void Button::setCallBackTo(cocos2d::Node* targetNode, const char* buttonName, const cocos2d::ui::Widget::ccWidgetTouchCallback &callback) {
    auto btnNode = targetNode->getChildByName(buttonName);
    if (nullptr == btnNode) {
        CCLOG("button node (name:%s) not found.", buttonName);
        return;
    }
    auto button = static_cast<cocos2d::ui::Button*>(btnNode);
    button->addTouchEventListener(callback);
}

void Button::setCallBackTo(cocos2d::Node* targetNode, const char* buttonName, const std::function<void()> &callbackBegan) {
    Button::setCallBackTo(targetNode, buttonName, [=](Ref*, cocos2d::ui::Widget::TouchEventType type){
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                callbackBegan();
                break;
            default:
                break;
        }
    });
}

void Button::setCallBackTo(cocos2d::Node* targetNode, const char* buttonName,
                               const std::function<void()> &callbackBegan,
                               const std::function<void()> &callbackEnd
                               ) {
    Button::setCallBackTo(targetNode, buttonName, [=](Ref*, cocos2d::ui::Widget::TouchEventType type){
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                callbackBegan();
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                callbackEnd();
                break;
            default:
                break;
        }
    });
}

void Button::setCallBackToLayerd(cocos2d::Node* targetNode, const char* nameNodeButtonLayerd, const char* nameInnerNodeButton, const std::function<void()> &callback) {
    auto node = targetNode->getChildByName(nameNodeButtonLayerd);
    if (node == nullptr) {
        CCLOG("node (name:%s) not found.", nameNodeButtonLayerd);
        return;
    }
    Button::setCallBackTo(node, nameInnerNodeButton, callback);
}

}
}