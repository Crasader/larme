#pragma once

#include "cocos2d.h"
#include "larme/template/Singleton.h"
#include "audio/include/AudioEngine.h"
#include "larme/audio/BgmManagerImpl.hpp"

using namespace cocos2d::experimental;

USING_NS_CC;

namespace larme {
namespace audio {

template<typename T>
class BgmManager : public larme::templates::Singleton<T>
{
public:
    BgmManager()
    :pimpl(new BgmManagerImpl())
    {
    }
    
    ~BgmManager() {
    }
    
    void registerBgm(int number, const std::string &audioPath) {
        this->pimpl->registerBgm(number, audioPath);
    }
    // 一から再生
    void play(int32_t bgmId, bool isCrossFade = false) {
        this->pimpl->play(bgmId, isCrossFade);
    }
    
    void stopAllAndPlay(int32_t bgmId, bool isCrossFade = false) {
        this->pimpl->stopAllAndPlay(bgmId, isCrossFade);
    }
    
    // 同じ曲を再生中なら処理なし
    void playContinue(int32_t bgmId, bool isCrossFade = false) {
        this->pimpl->playContinue(bgmId, isCrossFade);
    }
    
    void stopAllAndPlayContinue(int32_t bgmId, bool isCrossFade = false) {
        this->pimpl->stopAllAndPlayContinue(bgmId, isCrossFade);
    }
    
    void stopAll(bool fade) {
        this->pimpl->stopAll(fade);
    }
    
    void pause() {
        this->pimpl->pause();
    }
    
    void resume() {
        this->pimpl->resume();
    }
    
    float getVolume() {
        this->pimpl->getVolume();
    }
    
    void setVolume(float volume) {
        this->pimpl->setVolume(volume);
    }
    
    void setFadeDuration(float duration) {
        this->pimpl->setFadeDuration(duration);
    }
    
private:
    std::unique_ptr<BgmManagerImpl> pimpl;
};

}}