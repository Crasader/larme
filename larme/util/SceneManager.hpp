#pragma once

#include "cocos2d.h"
#include "larme/template/Singleton.h"

USING_NS_CC;


namespace larme {
namespace util {

class SceneManager : public larme::templates::Singleton<SceneManager>
{
public:
    SceneManager();
    void registerScene(int number, cocos2d::Scene* (*sceneCreate)());
    void replace(int number);
private:
    std::unordered_map<int, Scene*(*)()> sceneList;
};
    
}}
