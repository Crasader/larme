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
        this->forceStop();
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
        switch (this->state) {
            case STATE::PLAYING:
            case STATE::FADE_IN:
                // 何もしない
                return true;
            case STATE::ERROR:
            case STATE::END:
            case STATE::INIT:
            case STATE::PAUSE:
                // 再生してないので再生を試みる
                this->audioId = AudioEngine::play2d(this->bgmFilePath, true, this->volume);
                break;
            case STATE::FADE_OUT:
            default:
                // 再生中であるはずなので FADE_IN にする
                break;
        }
        if (this->audioId == AudioEngine::INVALID_AUDIO_ID) {
            this->state = STATE::ERROR;
            setScheduleRun(false);
            return false;
        }
        
        if (secondsFadeIn > 0) {
            AudioEngine::setVolume(audioId, 0.0f);
            this->fadeTimer = 0.0f;
            this->fadeDuration = secondsFadeIn;
            this->state = STATE::FADE_IN;
            setScheduleRun(true);
        } else {
            AudioEngine::setVolume(audioId, this->volume);
            this->state = PLAYING;
            setScheduleRun(false);
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
                //log("default(%d)", bgmId);// ここにはこない
                setScheduleRun(false);
                this->state = STATE::ERROR;
                break;
        }
    }
    
    void BgmObject::stop(float secondsFadeOut)
    {
        switch (this->state) {
            case STATE::ERROR:
            case STATE::END:
            case STATE::INIT:
            case STATE::PAUSE:
                this->state = STATE::END;
                return;
            default:
                break;
        }
        if (audioId == AudioEngine::INVALID_AUDIO_ID) {
            this->state = STATE::ERROR;
            setScheduleRun(false);
            return;
        }
        if (0 == secondsFadeOut) {
            this->state = STATE::END;
            AudioEngine::stop(audioId);
        } else if (0 < secondsFadeOut) {
            // FADE_OUT中ならば Timerリセットしない
            if (this->state != STATE::FADE_OUT) {
                fadeTimer = 0.0f;
            }
            this->state = STATE::FADE_OUT;
            fadeDuration = secondsFadeOut;
            setScheduleRun(true);
        }
    }
    
    void BgmObject::forceStop()
    {
        this->state = STATE::END;
        AudioEngine::stop(audioId);
        setScheduleRun(false);
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
