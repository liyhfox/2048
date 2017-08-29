//
//  GameOverLayer.hpp
//  2048
//
//  Created by L&L on 2017/4/11.
//
//

#ifndef GameOverLayer_hpp
#define GameOverLayer_hpp

#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public LayerColor
{
public:
    static GameOverLayer* create(const Color4B& color);
    virtual bool initWithColor(const Color4B& color);
    
    // Touch function
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {return true; };
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {};
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {};
};

#endif /* GameOverLayer_hpp */
