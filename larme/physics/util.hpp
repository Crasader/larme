#pragma once

#include "cocos2d.h"

USING_NS_CC;

namespace larme {
namespace physics {
namespace util {
    
    void setAllShapeCategoryBitmask(cocos2d::PhysicsBody* physicsBody, int categoryBitmask) {
        for (PhysicsShape* shape: physicsBody->getShapes()) {
            shape->setCategoryBitmask(categoryBitmask);
        }
    }
    
    void setAllShapeContactTestBitmask(cocos2d::PhysicsBody* physicsBody, int bitmask) {
        for (PhysicsShape* shape: physicsBody->getShapes()) {
            shape->setContactTestBitmask(bitmask);
        }
    }
    
}
}
}