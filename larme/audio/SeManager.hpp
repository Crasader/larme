#pragma once

#include "cocos2d.h"
#include "larme/template/Singleton.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d::experimental;
USING_NS_CC;

namespace larme {
namespace audio {
    
    template<typename T>
    class SeManager : public larme::templates::Singleton<T>
    {
    public:
        static SeManager* create() {
            SeManager* manager = new SeManager();
            
            if (manager && manager->init()) {
                return manager;
            }
            else {
                if (manager) { delete manager; }
                return NULL;
            }
        }
        
        void destroy() {
            delete this;
        }
        
        int32_t play(uint32_t seId, bool loop = false) {
            int32_t audioID = AudioEngine::play2d(this->seList.at(seId), loop, this->volume);
            return audioID;
        }
        
        void stop(int32_t audioId) {
            if (audioId != AudioEngine::INVALID_AUDIO_ID) {
                AudioEngine::stop(audioId);
            }
        }

        void pause(int32_t audioId) {
            if (audioId != AudioEngine::INVALID_AUDIO_ID) {
                AudioEngine::pause(audioId);
            }
        }
        
        void pause() {
            AudioEngine::pauseAll();
        }
        
        void resume(int32_t audioId) {
            if (audioId != AudioEngine::INVALID_AUDIO_ID) {
                AudioEngine::resume(audioId);
            }
        }
        
        void resume() {
            AudioEngine::resumeAll();
        }
        
        void preload(uint32_t seId) {
            AudioEngine::preload(this->seList.at(seId));
        }
        
        void registerSe(int number, const std::string &audioPath) {
            this->seList.insert(std::pair<int, std::string>(number, audioPath));
        }
        
        float getVolume() {
            return this->volume;
        }
        
        void setVolume(float volume) {
            this->volume = volume;
        }
    private:
        bool init() {
            return true;
        }
        
        float volume = 1.0f;
        std::unordered_map<int, std::string> seList;
    };
    
}}
