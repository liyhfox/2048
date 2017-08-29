//
//  PauseLayer.cpp
//  2048
//
//  Created by L&L on 2017/4/5.
//
//

#include <SimpleAudioEngine.h>
#include "PauseLayer.hpp"
#include "GameScene.h"

using namespace CocosDenshion;

PauseLayer* PauseLayer::create(const cocos2d::Color4B &color)
{
    PauseLayer *pLayer = new PauseLayer();
    if (pLayer && pLayer->initWithColor(color)) {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return nullptr;
}

bool PauseLayer::initWithColor(const cocos2d::Color4B &color)
{
    if (!LayerColor::initWithColor(color)) {
        return false;
    }
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    MenuItemFont::setFontName("Consolas");
    MenuItemFont::setFontSize(visibleSize.width * 0.1);
    
    auto menuItemContinue = MenuItemFont::create("CONTINUE", [this](Ref*) {
        this->removeFromParent();
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        Director::getInstance()->resume();
    });
    
    auto menuItemRestart = MenuItemFont::create("RESTART", [this](Ref*) {
        UserDefault::getInstance()->setBoolForKey("history", false);
        SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
        Director::getInstance()->replaceScene(GameScene::createScene());
        Director::getInstance()->resume();
    });
    
    auto menuItemExit = MenuItemFont::create("EXIT", [this](Ref*) {
        Director::getInstance()->end();
        exit(0);
    });
    
    Size winSize = Director::getInstance()->getWinSize();
    Point centerPos = Point(winSize.width / 2, winSize.height / 2);
    
    auto menu = Menu::create(menuItemContinue, menuItemRestart, menuItemExit, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);
    menu->setPosition(centerPos);
    
    
    
    return true;
    // todo
}
