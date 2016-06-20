#pragma once

#include "cocos2d.h"

USING_NS_CC;

namespace larme {
namespace util {
    
    /*
     これで考え方が良いのかどうかわからないが、このクラスは3つのレイヤーに分かれている
     1. sprite scroll - 登録したspriteを単純に移動させる
     2. rewind range - sprite を range内でループさせる
     x, y方向の二通り設定
     3. visible range - sprite が range内から外れると setVisible(false); となる
     上下左右それぞれ個別に設定できる
     
     usage:
     // 例1: 雲を左に移動させる
     NodeScroller nodeScroller = NodeScroller();
     nodeScroller.setRewindRangeX(-100, display.width + 100);
     // 雲の数だけ登録する
     nodeScroller.add(雲のSprite*, Vec2(-10, 0));
     // update()等の中で呼び出す
     nodeScroller.scrollSprites(Vec2(1, 0));
     nodeScroller.rewind();
     
     // 例2: 宇宙で輝く星を範囲内でループさせつつ、見えるのは宇宙空間のみに限定する
     NodeScroller nodeScroller = NodeScroller();
     nodeScroller.rangeVisibleBottom(1000);// 宇宙の高さ下限
     nodeScroller.setRewindRangeX(-100, display.width + 100);
     nodeScroller.setRewindRangeY(-100, display.height + 100);
     // 星の数だけ登録する
     nodeScroller.add(Sprite*, Vec2(0, 0));
     // update() 内
     nodeScroller.scrollSprites(Vec2(x, y));
     nodeScroller.rewind();
     nodeScroller.optimizeVisible();
     */
    
    class NodeScroller
    {
        // 可視範囲の定義
        // この範囲外に出ると isVisible(false); となる
    protected:
        bool isSetBorderVisibleTop;
        bool isSetBorderVisibleBottom;
        bool isSetBorderVisibleRight;
        bool isSetBorderVisibleLeft;
        CC_SYNTHESIZE_READONLY(float, borderVisibleTop, borderVisibleTop);
        CC_SYNTHESIZE_READONLY(float, borderVisibleBottom, borderVisibleBottom);
        CC_SYNTHESIZE_READONLY(float, borderVisibleRight, borderVisibleRight);
        CC_SYNTHESIZE_READONLY(float, borderVisibleLeft, borderVisibleLeft);
    public:
        void setRangeVisibleTop(float border);
        void setRangeVisibleBottom(float border);
        void setRangeVisibleRight(float border);
        void setRangeVisibleLeft(float border);
        
        // 巻き戻り範囲
        // この範囲外に出ると (Top - Bottom), (Right - Left) の距離だけ巻き戻る
        CC_SYNTHESIZE(float, borderRewindTop, BorderRewindTop);
        CC_SYNTHESIZE(float, borderRewindBottom, BorderRewindBottom);
        CC_SYNTHESIZE(float, borderRewindRight, BorderRewindRight);
        CC_SYNTHESIZE(float, borderRewindLeft, BorderRewindLeft);
    public:
        typedef std::pair<cocos2d::Node*, Vec2> scrollNode;
        
        NodeScroller();
        
        /**
         * scrollするspriteの登録
         */
        void add(cocos2d::Sprite* s, Vec2 vector);
        
        /*********************************************************
         * Sprite Scroll
         */
        
        /**
         * 登録されているspriteをscrollする
         */
        virtual void scrollNodes(const Vec2 &factor);
        
        
        /*********************************************************
         * Rewind
         */
        
        virtual void setRewindRangeX(float left, float right);
        
        virtual bool isSetRewindRangeX();
        
        virtual void setRewindRangeY(float bottom, float top);
        
        virtual bool isSetRewindRangeY();
        
        /**
         * 登録されているrewind rangeをscrollする
         */
        virtual void moveRewindRangeX(float x);
        virtual void moveRewindRangeY(float y);
        virtual void rewind();
        
        /*********************************************************
         * Visible
         */
        
        virtual void moveVisibleBorder(cocos2d::Vec2 moves);
        
        virtual void optimizeVisible();
    private:
        std::vector<scrollNode> nodes;
    };
    
}// namespace common
}// namespace larme