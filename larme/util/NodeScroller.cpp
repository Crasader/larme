#include "larme/util/NodeScroller.hpp"

USING_NS_CC;

namespace larme {
namespace util {
    
    
    NodeScroller::NodeScroller() {
    }
    
    void NodeScroller::setRangeVisibleTop(float border) {
        isSetBorderVisibleTop = true;
        borderVisibleTop = border;
    }
    
    void NodeScroller::setRangeVisibleRight(float border) {
        isSetBorderVisibleRight = true;
        borderVisibleRight = border;
    }
    
    void NodeScroller::setRangeVisibleLeft(float border) {
        isSetBorderVisibleLeft = true;
        borderVisibleLeft = border;
    }
    
    void NodeScroller::setRangeVisibleBottom(float border) {
        isSetBorderVisibleBottom = true;
        borderVisibleBottom = border;
    }
    
    void NodeScroller::add(cocos2d::Sprite* s, Vec2 vector) {
        this->nodes.push_back(scrollNode(s, vector));
    }

    void NodeScroller::scrollNodes(const Vec2 &factor) {
        for (auto scrollNode : this->nodes) {
            auto node = scrollNode.first;
            auto vector = scrollNode.second;
            
            auto newPosition =
            node->getPosition() +
            Vec2(vector.x * factor.x, vector.y * factor.y);
            node->setPosition(newPosition);
        }
    }
    
    
    void NodeScroller::setRewindRangeX(float left, float right) {
        this->borderRewindLeft = left;
        this->borderRewindRight = right;
    }
    
    bool NodeScroller::isSetRewindRangeX() {
        return borderRewindLeft != borderRewindRight;
    }
    
    void NodeScroller::setRewindRangeY(float bottom, float top) {
        this->borderRewindBottom = bottom;
        this->borderRewindTop = top;
    }
    
    bool NodeScroller::isSetRewindRangeY() {
        return borderRewindTop != borderRewindBottom;
    }
    
    void NodeScroller::moveRewindRangeX(float x) {
        this->borderRewindLeft += x;
        this->borderRewindRight += x;
    }
    void NodeScroller::moveRewindRangeY(float y) {
        this->borderRewindTop += y;
        this->borderRewindBottom += y;
    }
    void NodeScroller::rewind() {
        if (isSetRewindRangeX()) {
            float diffX = borderRewindRight - borderRewindLeft;
            for (auto scrollNode : this->nodes) {
                auto node = scrollNode.first;
                
                auto currentPosition = node->getPosition();
                auto newPosition = currentPosition;
                // 右に行き過ぎ
                if (borderRewindRight < currentPosition.x) {
                    int n = static_cast<int>(std::ceil((currentPosition.x - borderRewindRight) / diffX));
                    newPosition.x -= n * diffX;
                }
                // 左に行き過ぎ
                if (currentPosition.x < borderRewindLeft) {
                    int n = static_cast<int>(std::ceil(std::abs((currentPosition.x - borderRewindLeft) / diffX)));
                    newPosition.x += n * diffX;
                }
                node->setPosition(newPosition);
            }
        }
        if (isSetRewindRangeY()) {
            float diffY = borderRewindTop - borderRewindBottom;
            for (auto scrollSprite : this->nodes) {
                auto sprite = scrollSprite.first;
                
                auto currentPosition = sprite->getPosition();
                auto newPosition = currentPosition;
                // 上に行き過ぎ
                if (borderRewindTop < currentPosition.y) {
                    int n = static_cast<int>(std::ceil((currentPosition.y - borderRewindTop) / diffY));
                    newPosition.y -= n * diffY;
                }
                // 下に行き過ぎ
                if (currentPosition.y < borderRewindBottom) {
                    int n = static_cast<int>(std::ceil(std::abs((currentPosition.y - borderRewindBottom) / diffY)));
                    newPosition.y += n * diffY;
                }
                sprite->setPosition(newPosition);
            }
        }
    }
    
    void NodeScroller::moveVisibleBorder(cocos2d::Vec2 moves) {
        if (isSetBorderVisibleLeft) {
            borderVisibleLeft += moves.x;
        }
        if (isSetBorderVisibleRight) {
            borderVisibleRight += moves.x;
        }
        if (isSetBorderVisibleBottom) {
            borderVisibleBottom += moves.y;
        }
        if (isSetBorderVisibleTop) {
            borderVisibleTop += moves.y;
        }
    }
    
    void NodeScroller::optimizeVisible() {
        if (!isSetBorderVisibleBottom
            && !isSetBorderVisibleTop
            && !isSetBorderVisibleLeft
            && !isSetBorderVisibleRight
            ) {
            return;
        }
        // 上下
        std::function<bool(float)> fy;
        if (isSetBorderVisibleBottom && isSetBorderVisibleTop) {
            fy = [&](float y){ return borderVisibleBottom <= y && y <= borderRewindTop; };
        } else if (!isSetBorderVisibleBottom || isSetBorderVisibleTop) {
            fy = [&](float y){ return y <= borderRewindTop; };
        } else if (isSetBorderVisibleBottom || !isSetBorderVisibleTop) {
            fy = [&](float y){ return borderVisibleBottom <= y; };
        } else {
            fy = [&](float y){ return true; };
        }
        // 左右
        std::function<bool(float)> fx;
        if (isSetBorderVisibleLeft && isSetBorderVisibleRight) {
            fx = [&](float x){ return borderVisibleLeft <= x && x <= borderRewindRight; };
        } else if (!isSetBorderVisibleLeft || isSetBorderVisibleRight) {
            fx = [&](float x){ return x <= borderRewindRight; };
        } else if (isSetBorderVisibleLeft || !isSetBorderVisibleRight) {
            fx = [&](float x){ return borderVisibleLeft <= x; };
        } else {
            fx = [&](float x){ return true; };
        }
        for (auto scrollNode : this->nodes) {
            auto node = scrollNode.first;
            auto currentPosition = node->getPosition();
            node->setVisible(fy(currentPosition.y) && fx(currentPosition.x));
        }
    }
    
}}