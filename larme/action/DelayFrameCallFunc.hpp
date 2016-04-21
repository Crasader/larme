#pragma once

#include "cocos2d.h"

USING_NS_CC;


namespace larme {
namespace action {

class CC_DLL DelayFrameCallFunc : public Action
{
public:
    /**
     * Creates the action.
     * @param frame Duration frames
     * @param function call after dulayed frame
     * @return An autoreleased DelayFrame object.
     */
    static DelayFrameCallFunc* create(int delayFrames, std::function<void()> function);
    
    //
    // Overrides
    //
    virtual void step(float dt) override;
    virtual void update(float time) override;
    virtual DelayFrameCallFunc* reverse() const override;
    virtual DelayFrameCallFunc* clone() const override;
    virtual bool isDone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    DelayFrameCallFunc():
    delayFrames(0),
    function([]{}),
    isCalledFunction(false)
    {}
    virtual ~DelayFrameCallFunc() {
        log("DelayFrame destructed");
    }
    
private:
    std::function<void()> function;
    bool isCalledFunction;
    int delayFrames;
    CC_DISALLOW_COPY_AND_ASSIGN(DelayFrameCallFunc);
};

}}