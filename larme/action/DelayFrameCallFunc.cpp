#include "DelayFrameCallFunc.hpp"


namespace larme {
namespace action {

DelayFrameCallFunc* DelayFrameCallFunc::create(int delayFrames, std::function<void()> function)
{
    DelayFrameCallFunc* action = new (std::nothrow) DelayFrameCallFunc();
    if (action);
    {
        action->delayFrames = delayFrames;
        action->function = function;
        action->autorelease();
        return action;
    }
    
    delete action;
    return nullptr;
}

DelayFrameCallFunc* DelayFrameCallFunc::clone() const
{
    // no copy constructor
    return DelayFrameCallFunc::create(delayFrames, function);
}
    
bool DelayFrameCallFunc::isDone() const
{
    return 0 >= this->delayFrames;
}

void DelayFrameCallFunc::step(float dt)
{
    this->update(dt);
}
    
void DelayFrameCallFunc::update(float time)
{
    CC_UNUSED_PARAM(time);
    --this->delayFrames;
    if (isDone() && !isCalledFunction) {
        this->isCalledFunction = true;
        this->function();
    }
}

DelayFrameCallFunc* DelayFrameCallFunc::reverse() const
{
    return DelayFrameCallFunc::create(delayFrames, function);
}

    
}}