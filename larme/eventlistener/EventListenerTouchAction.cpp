#include "EventListenerTouchAction.hpp"

#include <array>


namespace larme{
namespace eventlistener{

/**
 * class TouchInfo
 */
class TouchInfo
{
    CC_SYNTHESIZE(bool, isMoving, IsMoving);
    CC_SYNTHESIZE(cocos2d::Touch*, touch, Touch);
public:
    TouchInfo(cocos2d::Touch* touch):
    touch(touch) {
    }
    void computeMove(float panRange, cocos2d::Touch* touch) {
        if (this->isMoving) {
            return;
        }
        float moveLength = (touch->getStartLocation() - touch->getLocation()).length();
        if (panRange < moveLength) {
            this->isMoving = true;
        }
    }
};

/**
 * class EventListenerTouchAction::Impl
 */
class EventListenerTouchAction::Impl
{
    CC_SYNTHESIZE(float, panRange, PanRange);
    CC_SYNTHESIZE(EventListenerTouchAction*, listener, Listener);
public:
    void onTouchesMove(const std::vector<Touch*>& touches, Event* event);
    void onTouchesCancelled(const std::vector<Touch*>& touches, Event* event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
private:
    std::array<TouchInfo*, 5> touchInfos;
    void removeTouchInfo(cocos2d::Touch* touch);
    void addTouchInfo(cocos2d::Touch* touch);
    bool isSingleTouch();
    Vec2 getCenterCurrent();
    Vec2 getCenterPrevious();
    float getDistanceTotalFromCenterCurrent();
    float getDistanceTotalFromCenterPrevious();
};

Vec2 EventListenerTouchAction::Impl::getCenterCurrent() {
    int total = 0;
    cocos2d::Vec2 center;
    for (auto touchInfo : touchInfos) {
        if (nullptr == touchInfo) { continue; }
        ++total;
        center += touchInfo->getTouch()->getLocation();
    }
    if (0 == total) {
        return Vec2::ZERO;
    }
    return center *= (1.0f/total);
}

    
Vec2 EventListenerTouchAction::Impl::getCenterPrevious() {
    int total = 0;
    cocos2d::Vec2 center;
    for (auto touchInfo : touchInfos) {
        if (nullptr == touchInfo) { continue; }
        ++total;
        center += touchInfo->getTouch()->getPreviousLocation();
    }
    if (0 == total) {
        return Vec2::ZERO;
    }
    return center *= (1.0f/total);
}
    
    
float EventListenerTouchAction::Impl::getDistanceTotalFromCenterCurrent() {
    Vec2 center = this->getCenterCurrent();
    float total = 0;
    for (auto touchInfo : touchInfos) {
        if (nullptr == touchInfo) { continue; }
        total += (center - touchInfo->getTouch()->getLocation()).length();
    }
    return total;
}

float EventListenerTouchAction::Impl::getDistanceTotalFromCenterPrevious() {
    Vec2 center = this->getCenterPrevious();
    float total = 0;
    for (auto touchInfo : touchInfos) {
        if (nullptr == touchInfo) { continue; }
        total += (center - touchInfo->getTouch()->getPreviousLocation()).length();
    }
    return total;
}

bool EventListenerTouchAction::Impl::isSingleTouch() {
    int count = 0;
    for (TouchInfo* touchInfo : touchInfos) {
        if (nullptr == touchInfo) { continue; }
        ++count;
    }
    return 1 == count;
}

void EventListenerTouchAction::Impl::removeTouchInfo(cocos2d::Touch *touch)
{
    if (nullptr != this->touchInfos[touch->getID()]) {
        delete this->touchInfos[touch->getID()];
        this->touchInfos[touch->getID()] = nullptr;
    }
}

void EventListenerTouchAction::Impl::addTouchInfo(cocos2d::Touch *touch)
{
    this->removeTouchInfo(touch);
    this->touchInfos[touch->getID()] = new TouchInfo(touch);
}

void EventListenerTouchAction::Impl::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    for (Touch* touch: touches) {
        this->addTouchInfo(touch);
    }
    this->listener->onTouchesActionBegan(touches, event);
}

void EventListenerTouchAction::Impl::onTouchesMove(const std::vector<Touch*>& touches, Event* event)
{
    for (Touch* touch: touches) {
        this->touchInfos[touch->getID()]->computeMove(10, touch);
    }
    bool isSingleTouch = this->isSingleTouch();
    // Pan action
    if (isSingleTouch) {
        Touch* touch = touches[0];
        if (this->touchInfos[touch->getID()]->getIsMoving()) {
            this->listener->onTouchesActionPan(
               touch->getLocation() - touch->getPreviousLocation()
            );
        }
    }
    // Zoom action
    if (!isSingleTouch) {
        // moving な touch があるか？
        bool hasMoving = false;
        for (auto touchInfo : touchInfos) {
            if (nullptr == touchInfo) { continue; }
            if (touchInfo->getIsMoving()) {
                hasMoving = true;
                break;
            }
        }
        // あったらzoom action
        if (hasMoving) {
            float distanceTotalCur = this->getDistanceTotalFromCenterCurrent();
            float distanceTotalPre = this->getDistanceTotalFromCenterPrevious();
            this->listener->onTouchesActionZoom(distanceTotalCur - distanceTotalPre);
        }
    }
    this->listener->onTouchesActionMove(touches, event);
}

void EventListenerTouchAction::Impl::onTouchesCancelled(const std::vector<Touch*>& touches, Event* event)
{
    this->listener->onTouchesActionCancelled(touches, event);
}

void EventListenerTouchAction::Impl::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    for (auto touch: touches) {
        this->removeTouchInfo(touch);
    }
    this->listener->onTouchesActionEnded(touches, event);
}

/**
 * methods EventListenerTouchAction
 */
EventListenerTouchAction* EventListenerTouchAction::create()
{
    auto ret = new (std::nothrow) EventListenerTouchAction();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

EventListenerTouchAction::EventListenerTouchAction()
: pimpl(new EventListenerTouchAction::Impl())
{
    pimpl->setListener(this);
    this->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event* event) {
        this->pimpl->onTouchesBegan(touches, event);
    };
    
    this->onTouchesMoved = [=](const std::vector<Touch*>& touches, Event* event) {
        this->pimpl->onTouchesMove(touches, event);
    };
    
    this->onTouchesEnded = [=](const std::vector<Touch*>& touches, Event* event) {
        this->pimpl->onTouchesEnded(touches, event);
    };
    
    this->onTouchesCancelled = [=](const std::vector<Touch*>& touches, Event* event) {
        this->pimpl->onTouchesCancelled(touches, event);
    };
    this->onTouchesActionBegan = [](const std::vector<Touch*>& touches, Event* event){};
    this->onTouchesActionCancelled = [](const std::vector<Touch*>& touches, Event* event){};
    this->onTouchesActionEnded = [](const std::vector<Touch*>& touches, Event* event){};
    this->onTouchesActionMove = [](const std::vector<Touch*>& touches, Event* event){};
    this->onTouchesActionPan = [](Vec2 distance){};
    this->onTouchesActionZoom = [](float zoomRate){};
}

EventListenerTouchAction::~EventListenerTouchAction(){}

}}