//
//  GameOverLayer.cpp
//  2048
//
//  Created by L&L on 2017/4/11.
//
//

#include "GameOverLayer.hpp"
#include "GameScene.h"

GameOverLayer* GameOverLayer::create(const cocos2d::Color4B &color)
{
    auto layer = new GameOverLayer();
    if (layer && layer->initWithColor(color)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool GameOverLayer::initWithColor(const cocos2d::Color4B &color)
{
    if (!LayerColor::initWithColor(color)) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size winSize = Director::getInstance()->getWinSize();
    
    Point labelPos = Point(winSize.width / 2, winSize.height / 1.4);
    auto gameOverLabel = Label::createWithSystemFont("Game Over!", "consolas", visibleSize.width * 0.13);
    gameOverLabel->setPosition(labelPos);
    this->addChild(gameOverLabel);
    
    MenuItemFont::setFontName("consolas");
    MenuItemFont::setFontSize(visibleSize.width * 0.09);
    
    auto menuItemRestart = MenuItemFont::create("Restart", [](Ref*) {
        Director::getInstance()->replaceScene(GameScene::createScene());
    });
    
    auto menuItemExit = MenuItemFont::create("Exit", [](Ref*) {
        Director::getInstance()->end();
        exit(0);
    });
    
    Point menuPos = Point(winSize.width / 2, winSize.height / 3.8);
    auto menu = Menu::create(menuItemRestart, menuItemExit, NULL);
    menu->alignItemsHorizontallyWithPadding(visibleSize.width * 0.1);
    menu->setPosition(menuPos);
    this->addChild(menu);
    
    UserDefault::getInstance()->setBoolForKey("history", false);
    
    return true;
}

