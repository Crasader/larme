#pragma once

#include "cocos2d.h"

USING_NS_CC;

namespace larme{
namespace eventlistener{

class EventListenerTouchAction : public EventListenerTouchAllAtOnce
{
public:
    
    static EventListenerTouchAction* create();
    
    EventListenerTouchAction();
    ~EventListenerTouchAction();
    
    ccTouchesCallback onTouchesActionMove;
    ccTouchesCallback onTouchesActionBegan;
    ccTouchesCallback onTouchesActionEnded;
    ccTouchesCallback onTouchesActionCancelled;
    
    std::function<void(float zoomRate)> onTouchesActionZoom;
    std::function<void(Vec2 distance)> onTouchesActionPan;
private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
};

}
}