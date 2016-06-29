#include "cocos2d.h"
#include "BgmManager.hpp"
#include "BgmObject.hpp"

USING_NS_CC;

namespace larme {
namespace audio {
    
    void BgmManager::clean() {
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
    
    //template<typename T>
    void BgmManager::play(int32_t bgmId, bool isCrossFade) {
        this->clean();
        auto bgmObject = BgmObject::create(bgmId, this->bgmList.at(bgmId), this->volume);
        this->playBgmObject(bgmObject, isCrossFade);
        this->bgmObjects.push_back(bgmObject);
    }
    
    //template<typename T>
    void BgmManager::stopAllAndPlay(int32_t bgmId, bool isCrossFade) {
        this->stopAll(isCrossFade);
        this->clean();
        this->play(bgmId, isCrossFade);
    }
    
    //template<typename T>
    void BgmManager::playContinue(int32_t bgmId, bool isCrossFade) {
        bool isPlayed = false;
        for (auto bgmObject : this->bgmObjects) {
            if (bgmId == bgmObject->getBgmId()) {
                this->playBgmObject(bgmObject, isCrossFade);
                isPlayed = true;
            }
        }
        if (!isPlayed) {
            this->play(bgmId, isCrossFade);
        }
    }
    
    //template<typename T>
    void BgmManager::stopAllAndPlayContinue(int32_t bgmId, bool isCrossFade) {
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
    
    //template<typename T>
    void BgmManager::stopAll(bool isCrossFade) {
        for (auto bgmObject : this->bgmObjects) {
            this->stopBgmObject(bgmObject, isCrossFade);
        }
    }
    
    //template<typename T>
    void BgmManager::pause() {
        for (auto bgmObject : this->bgmObjects) {
            bgmObject->pause();
        }
    }
    
    //template<typename T>
    void BgmManager::resume() {
        for (auto bgmObject : this->bgmObjects) {
            bgmObject->resume();
        }
    }
    
    //template<typename T>
    void BgmManager::setVolume(float volume) {
        this->volume = volume;
        for (auto bgmObject : this->bgmObjects) {
            bgmObject->setVolume(this->volume);
        }
    }

}}