#include "SceneManager.hpp"


namespace larme {
namespace util {

/**
 * methods SceneManager
 */
SceneManager::SceneManager(){}
    
void SceneManager::registerScene(int number, cocos2d::Scene* (*sceneCreate)()) {
    this->sceneList.insert(std::pair<int, Scene*(*)()>(number, sceneCreate));
}

void SceneManager::replace(int number) {
    if (0 == this->sceneList.count(number)) {
        log("Scene number %d not found", number);
    }
    auto scene = this->sceneList.at(number)();
    Director::getInstance()->replaceScene(scene);
}
    
void SceneManager::runWith(int number) {
    if (0 == this->sceneList.count(number)) {
        log("Scene number %d not found", number);
    }
    auto scene = this->sceneList.at(number)();
    Director::getInstance()->runWithScene(scene);
}

}}

