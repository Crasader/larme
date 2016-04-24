#pragma once

#include "cocos2d.h"
#include "larme/template/Singleton.h"

USING_NS_CC;

namespace larme {
namespace util {

template<typename T>
class SceneManager : public larme::templates::Singleton<T>
{
public:
    template<typename S> S createScene(int number) {
        cocos2d::Scene* scene = this->functionSceneCreate.at(number)();
        return static_cast<S>(scene);
        // should be dynamic_cast?
    }
    
    void registerScene(int number, cocos2d::Scene* (*sceneCreate)()) {
        this->functionSceneCreate.insert(std::pair<int, Scene*(*)()>(number, sceneCreate));
    }
    
    void replace(int number) {
        if (0 == this->functionSceneCreate.count(number)) {
            log("Scene number %d not found", number);
        }
        auto scene = this->functionSceneCreate.at(number)();
        Director::getInstance()->replaceScene(scene);
    }
    
    void replace(Scene* scene) {
        Director::getInstance()->replaceScene(scene);
    }
    
    void runWith(int number) {
        if (0 == this->functionSceneCreate.count(number)) {
            log("Scene number %d not found", number);
        }
        auto scene = this->functionSceneCreate.at(number)();
        Director::getInstance()->runWithScene(scene);
    }
    
private:
    std::unordered_map<int, Scene*(*)()> functionSceneCreate;
};
    
}}
