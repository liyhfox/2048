//
//  WelcomeScene.hpp
//  2048
//
//  Created by L&L on 2017/4/6.
//
//

#ifndef WelcomeScene_hpp
#define WelcomeScene_hpp

#include "cocos2d.h"

USING_NS_CC;

class WelcomeScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(WelcomeScene);
    
    ~WelcomeScene() {};
    
    // Touch function
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {return true; };
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {};
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {};
};

#endif /* WelcomeScene_hpp */
