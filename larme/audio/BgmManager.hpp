#pragma once

#include "cocos2d.h"
#include "larme/template/Singleton.h"
#include "audio/include/AudioEngine.h"
#include "BgmObject.hpp"

using namespace cocos2d::experimental;

USING_NS_CC;

namespace larme {
namespace audio {

//template<typename T>
class BgmManager : public larme::templates::Singleton<BgmManager>
{
    CC_SYNTHESIZE(float, fadeDuration, FadeDuration)
public:
    BgmManager() {
        this->init();
    }
    ~BgmManager() {
        this->destroy();
    }
    
    void registerBgm(int number, const std::string &audioPath) {
        this->bgmList.insert(std::pair<int, std::string>(number, audioPath));
    }
    
    // 一から再生
    void play(int32_t bgmId, bool isCrossFade = false);
    // 同じ曲を再生中なら処理なし
    void playContinue(int32_t bgmId, bool isCrossFade = false);
    void stop(bool fade);
    void pause();
    void resume();
    float getVolume() { return volume; }
    void setVolume(float volume);
    
private:
    virtual void init() {
        this->volume = 1.0f;
        this->fadeDuration = 2.0f;
        return;
    }
    void destroy() {
        delete this;
    }
    
    void stopAll();
    void clean();
    
private:
    cocos2d::Scheduler* scheduler;
    std::list<BgmObject*> bgmObjects;
    float volume;
    std::unordered_map<int, std::string> bgmList;
};

}}
