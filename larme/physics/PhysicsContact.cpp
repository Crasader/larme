#include "PhysicsContact.hpp"

USING_NS_CC;

namespace larme {
namespace physics {

PhysicsContact::DIMENSION PhysicsContact::getDimensionSquareContacts(cocos2d::PhysicsContact& contact)
{
    auto contactData = contact.getContactData();
    if (2 != contactData->count) {
        return DIMENSION::NONE;
    }
    //log("(%f, %f), (%f, %f)", contactData->points[0].x, contactData->points[0].y, contactData->points[1].x, contactData->points[1].y);
    if (contactData->points[0].x == contactData->points[1].x) {
        return DIMENSION::VERTICAL;
    } else if (contactData->points[0].y == contactData->points[1].y) {
        return DIMENSION::HORIZONTAL;
    }
    return DIMENSION::NONE;
}
    
PhysicsContact::SIDE PhysicsContact::getSideSquareContacts(const cocos2d::PhysicsShape* shape, cocos2d::PhysicsContact& contact)
{
    PhysicsContact::DIMENSION dimension = getDimensionSquareContacts(contact);
    if (dimension == PhysicsContact::DIMENSION::NONE) {
        return SIDE::NONE;
    }
    auto contactData = contact.getContactData();
    if (dimension == PhysicsContact::DIMENSION::VERTICAL) {
        if (shape->getBody()->getPosition().x < contactData->points[0].x) {
            return SIDE::RIGHT;
        } else {
            return SIDE::LEFT;
        }
    } else if (dimension == PhysicsContact::DIMENSION::HORIZONTAL) {
        if (shape->getBody()->getPosition().y < contactData->points[0].y) {
            return SIDE::UP;
        } else {
            return SIDE::DOWN;
        }
    }
    return SIDE::NONE;
}

}
}