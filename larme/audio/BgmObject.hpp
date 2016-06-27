#pragma once

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

namespace larme {
namespace audio {
    
    class BgmObject
    {
        CC_SYNTHESIZE_READONLY(std::string, bgmFilePath, BgmFilePath)
        CC_SYNTHESIZE_READONLY(int32_t, bgmId, BgmId)
    public:
        enum STATE {
            INIT,
            PLAYING,
            PAUSE,
            END,
            FADE_OUT,
            FADE_IN,
            ERROR,
        };
        CC_SYNTHESIZE_READONLY(STATE, state, State);
        
    private:
        BgmObject(int32_t bgmId, std::string bgmFilePath, float volume);
        
    public:
        static BgmObject* create(int32_t bgmId, std::string bgmFilePath, float volume);
        
    private:
        void setScheduleRun(bool onRunning);
        
    public:
        virtual ~BgmObject();
        void update(float delta);
        
    public:
        bool play(float secondsFadeIn = 0.0f);
        void stop(float secondsFadeOut = 0.0f);
        void pause();
        void resume();
        
        void setVolume(float volume);
        
    private:
        float fadeTimer;
        float fadeDuration;
        float volume;
        Scheduler* scheduler;
        int32_t audioId;
    };
    
}}
