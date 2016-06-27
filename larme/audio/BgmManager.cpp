#include "cocos2d.h"
#include "BgmManager.hpp"
#include "BgmObject.hpp"

USING_NS_CC;

namespace larme {
namespace audio {
    
    void BgmManager::clean() {
        //log("clean bgm audio from: %d", (int)this->bgmObjects.size());
        std::list<BgmObject*>::iterator it;
        for (it = this->bgmObjects.begin(); it != this->bgmObjects.end(); ) {
            switch ((*it)->getState()) {
                case BgmObject::STATE::END:
                case BgmObject::STATE::ERROR:
                case BgmObject::STATE::INIT:
                    delete *it;
                    it = this->bgmObjects.erase(it);
                    break;
                default:
                    it++;
                    break;
            }
        }
        //log("clean bgm audio to: %d", (int)this->bgmObjects.size());
    }
    
    //template<typename T>
    void BgmManager::play(int32_t bgmId, bool isCrossFade) {
        this->clean();
        this->stop(isCrossFade);
        auto bgmObject = BgmObject::create(bgmId, this->bgmList.at(bgmId), this->volume);
        if (isCrossFade) {
            bgmObject->play(this->fadeDuration);
        } else {
            bgmObject->play();
        }
        this->bgmObjects.push_back(bgmObject);
    }
    
    //template<typename T>
    void BgmManager::playContinue(int32_t bgmId, bool isCrossFade) {
        for (auto bgmObject : this->bgmObjects) {
            if (bgmId == bgmObject->getBgmId()) {
                return;
            }
        }
        this->play(bgmId, isCrossFade);
    }
    
    //template<typename T>
    void BgmManager::stop(bool fade) {
        for (auto bgmObject : this->bgmObjects) {
            if (fade) {
                bgmObject->stop(this->fadeDuration);
            } else {
                bgmObject->stop();
            }
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
    
    //template<typename T>
    void BgmManager::stopAll() {
        for (auto bgmObject : this->bgmObjects) {
            bgmObject->stop(0);
        }
    }

}}