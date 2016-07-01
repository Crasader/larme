#pragma once

#include "cocos2d.h"
#include "larme/template/Singleton.h"
#include "audio/include/AudioEngine.h"
#include "BgmObject.hpp"

using namespace cocos2d::experimental;

USING_NS_CC;

namespace larme {
namespace audio {

class BgmManagerImpl
{
public:
    BgmManagerImpl() {
        this->init();
        
    }
    ~BgmManagerImpl() {
        this->destroy();
    }
    
    void registerBgm(int number, const std::string &audioPath) {
        this->bgmList.insert(std::pair<int, std::string>(number, audioPath));
    }
    
    // 一から再生
    void play(int32_t bgmId, bool isCrossFade = false) {
        this->clean();
        auto bgmObject = BgmObject::create(bgmId, this->bgmList.at(bgmId), this->volume);
        this->playBgmObject(bgmObject, isCrossFade);
        this->bgmObjects.push_back(bgmObject);
    }
    
    void stopAllAndPlay(int32_t bgmId, bool isCrossFade = false) {
        this->stopAll(isCrossFade);
        this->clean();
        this->play(bgmId, isCrossFade);
    }
    
    // 同じ曲を再生中なら処理なし
    void playContinue(int32_t bgmId, bool isCrossFade = false) {
        bool isPlayed = false;
        for (auto bgmObject : this->bgmObjects) {
            if (bgmId == bgmObject->getBgmId()) {
                this->playBgmObject(bgmObject, isCrossFade);
                isPlayed = true;
            }
        }
        this->clean();
        if (!isPlayed) {
            this->play(bgmId, isCrossFade);
        }
    }
    
    void stopAllAndPlayContinue(int32_t bgmId, bool isCrossFade = false) {
        bool isPlayed = false;
        for (auto bgmObject : this->bgmObjects) {
            if (bgmId == bgmObject->getBgmId()) {
                this->playBgmObject(bgmObject, isCrossFade);
                isPlayed = true;
            } else {
                this->stopBgmObject(bgmObject, isCrossFade);
            }
        }
        this->clean();
        if (!isPlayed) {
            this->play(bgmId, isCrossFade);
        }
    }
    
    void stopAll(bool isCrossFade) {
        for (auto bgmObject : this->bgmObjects) {
            this->stopBgmObject(bgmObject, isCrossFade);
        }
        this->clean();
    }
    
    void pause() {
        for (auto bgmObject : this->bgmObjects) {
            bgmObject->pause();
        }
    }
    
    void resume() {
        for (auto bgmObject : this->bgmObjects) {
            bgmObject->resume();
        }
    }
    
    float getVolume() {
        return volume;
    }
    
    void setVolume(float volume) {
        this->volume = volume;
        for (auto bgmObject : this->bgmObjects) {
            bgmObject->setVolume(this->volume);
        }
    }
    
private:
    virtual void init() {
        this->volume = 1.0f;
        this->fadeDuration = 2.0f;
        return;
    }
    void destroy() {
        delete this;
    }
    
    void clean() {
        log("clean bgm audio from: %d", (int)this->bgmObjects.size());
        std::list<BgmObject*>::iterator it;
        for (it = this->bgmObjects.begin(); it != this->bgmObjects.end(); ) {
            //log("state: %d", (int)(*it)->getState());
            switch ((*it)->getState()) {
                case BgmObject::STATE::END:
                case BgmObject::STATE::ERROR:
                case BgmObject::STATE::INIT:
                case BgmObject::STATE::PAUSE:
                    delete *it;
                    it = this->bgmObjects.erase(it);
                    break;
                default:
                    it++;
                    break;
            }
        }
        log("clean bgm audio to: %d", (int)this->bgmObjects.size());
    }
    
    void playBgmObject(BgmObject* bgmObject, bool isCrossfade) {
        if (isCrossfade) {
            bgmObject->play(this->fadeDuration);
        } else {
            bgmObject->play();
        }
    }
    
    void stopBgmObject(BgmObject* bgmObject, bool isCrossfade) {
        if (isCrossfade) {
            bgmObject->stop(this->fadeDuration);
        } else {
            bgmObject->stop();
        }
    }
    
private:
    std::list<BgmObject*> bgmObjects;
    float volume;
    std::unordered_map<int, std::string> bgmList;
    CC_SYNTHESIZE(float, fadeDuration, FadeDuration)
};

}}