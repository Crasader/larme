#include "BgmObject.hpp"

#include "audio/include/AudioEngine.h"

using namespace cocos2d::experimental;

USING_NS_CC;

namespace larme {
namespace audio {
    
    BgmObject::BgmObject(int32_t bgmId, std::string bgmFilePath, float volume)
    {
        this->state = STATE::INIT;
        this->bgmId = bgmId;
        this->bgmFilePath = bgmFilePath;
        this->volume = volume;
        this->audioId = AudioEngine::INVALID_AUDIO_ID;
        this->scheduler = Director::getInstance()->getScheduler();
        this->scheduler->scheduleUpdate(this, 0, true);// 初期はpause
    }
    
    BgmObject::~BgmObject()
    {
        this->stop();
        this->scheduler->unscheduleUpdate(this);
        CC_SAFE_RELEASE_NULL(this->scheduler);
    }
    
    BgmObject* BgmObject::create(int32_t bgmId, std::string bgmFilePath, float volume)
    {
        BgmObject* object = new BgmObject(bgmId, bgmFilePath, volume);
        return object;
    }
    
    void BgmObject::setScheduleRun(bool onRunning)
    {
        if (onRunning) {
            this->scheduler->scheduleUpdate(this, 0, false);
        } else {
            this->scheduler->scheduleUpdate(this, 0, true);
        }
    }
    
    bool BgmObject::play(float secondsFadeIn)
    {
        this->audioId = AudioEngine::play2d(this->bgmFilePath, true, this->volume);
        if (this->audioId == AudioEngine::INVALID_AUDIO_ID) {
            this->state = STATE::ERROR;
            return false;
        }
        
        if (secondsFadeIn > 0) {
            fadeTimer = 0.0f;
            fadeDuration = secondsFadeIn;
            AudioEngine::setVolume(audioId, 0.0f);
            this->state = FADE_IN;
            setScheduleRun(true);
        } else {
            this->state = PLAYING;
        }
        return true;
    }
    
    void BgmObject::update(float delta)
    {
        if (audioId == AudioEngine::INVALID_AUDIO_ID) {
            this->state = STATE::ERROR;
            setScheduleRun(false);
            return;
        }
        
        fadeTimer += delta;
        switch (state) {
            case STATE::FADE_IN:
            {
                float targetVolume = volume * (fadeTimer / fadeDuration);
                targetVolume = std::min(volume, targetVolume);
                //log("IN(%d) targetVolume: %f, %f, %f, %f", bgmId, targetVolume, fadeTimer, fadeDuration, volume);
                AudioEngine::setVolume(audioId, targetVolume);
                if (fadeTimer > fadeDuration) {
                    this->state = STATE::PLAYING;
                    setScheduleRun(false);
                }
            }
                break;
            case STATE::FADE_OUT:
            {
                float targetVolume = volume * (1 - (fadeTimer / fadeDuration));
                targetVolume = std::max(0.0f, targetVolume);
                //log("OUT(%d) targetVolume: %f, %f, %f, %f", bgmId, targetVolume, fadeTimer, fadeDuration, volume);
                AudioEngine::setVolume(audioId, targetVolume);
                if (fadeTimer > fadeDuration) {
                    this->stop();
                    this->state = STATE::END;
                    setScheduleRun(false);
                }
            }
                break;
            default:
                setScheduleRun(false);
                this->state = STATE::ERROR;
                break;
        }
    }
    
    void BgmObject::stop(float secondsFadeOut)
    {
        if (audioId == AudioEngine::INVALID_AUDIO_ID) {
            this->state = STATE::ERROR;
            setScheduleRun(false);
            return;
        }
        if (0 == secondsFadeOut) {
            this->state = STATE::END;
            AudioEngine::stop(audioId);
        } else if (0 < secondsFadeOut) {
            this->state = STATE::FADE_OUT;
            fadeTimer = 0.0f;
            fadeDuration = secondsFadeOut;
            setScheduleRun(true);
        }
    }
    
    void BgmObject::pause()
    {
        this->state = STATE::PAUSE;
        if (audioId != AudioEngine::INVALID_AUDIO_ID) {
            AudioEngine::pause(audioId);
        }
    }
    
    void BgmObject::resume()
    {
        this->state = STATE::PLAYING;
        if (audioId != AudioEngine::INVALID_AUDIO_ID) {
            AudioEngine::resume(audioId);
        }
    }
    
    void BgmObject::setVolume(float volume)
    {
        this->volume = volume;
        if (audioId != AudioEngine::INVALID_AUDIO_ID) {
            AudioEngine::setVolume(audioId, volume);
        }
    }
    
}}
