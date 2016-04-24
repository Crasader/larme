#pragma once

#include "cocos2d.h"

USING_NS_CC;

namespace larme {
namespace layer {
    
    LayerColor* createUntouchableLayer(const cocos2d::Color4B &color) {
        auto layer = LayerColor::create(color);
        // 半透明部分をタッチ不可能にするためのリスナー
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch *touch, Event *event)->bool{
            // このイベントは登録しないとエラーが出る
            return true;
        };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);
        return layer;
    }
    
}
}