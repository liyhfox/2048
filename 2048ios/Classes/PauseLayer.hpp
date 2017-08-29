//
//  PauseLayer.hpp
//  2048
//
//  Created by L&L on 2017/4/5.
//
//

#ifndef PauseLayer_hpp
#define PauseLayer_hpp

#include "cocos2d.h"

USING_NS_CC;

class PauseLayer : public LayerColor
{
public:
    static PauseLayer* create(const Color4B& color);
    virtual bool initWithColor(const Color4B& color);
    
    ~PauseLayer() {};
    
    // Touch function
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {return true; };
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {};
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {};
};

#endif /* PauseLayer_hpp */
