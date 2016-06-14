#pragma once

#include "cocos2d.h"

namespace larme {
namespace physics {

class PhysicsContact
{
        
public:
    enum class DIMENSION : int {
        NONE,
        VERTICAL,
        HORIZONTAL,
    };
    
    enum class SIDE : int {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };
    
    static PhysicsContact::DIMENSION getDimensionSquareContacts(cocos2d::PhysicsContact& contact);
    static PhysicsContact::SIDE getSideSquareContacts(const cocos2d::PhysicsShape* shape, cocos2d::PhysicsContact& contact);
};

}
}