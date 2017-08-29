//
//  WelcomeScene.cpp
//  2048
//
//  Created by L&L on 2017/4/6.
//
//

#include <SimpleAudioEngine.h>
#include "WelcomeScene.hpp"
#include "GameScene.h"

using namespace CocosDenshion;

Scene* WelcomeScene::createScene()
{
    Scene *scene = Scene::create();
    
    Layer *layer = WelcomeScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool WelcomeScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto layerColorBG = LayerColor::create(Color4B(180, 170, 160, 255));
    this->addChild(layerColorBG);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size winSize = Director::getInstance()->getWinSize();
    
    Point namePos = Point(winSize.width / 2, winSize.height / 1.5);
    auto nameLabel = Label::createWithSystemFont("2048", "consolas", visibleSize.width * 0.2);
    nameLabel->setPosition(namePos);
    this->addChild(nameLabel);

    MenuItemFont::setFontName("consolas");
    MenuItemFont::setFontSize(visibleSize.width * 0.1);
    
    auto menuItemNew = MenuItemFont::create("New", [this](Ref*) {
        UserDefault::getInstance()->setBoolForKey("history", false);
        Director::getInstance()->replaceScene(GameScene::createScene());
    });
    
    auto menuItemContinue = MenuItemFont::create("Continue", [this](Ref*) {
    Director::getInstance()->replaceScene(GameScene::createScene());
    });
    
    Point startPos = Point(winSize.width / 2, winSize.height / 4);
    auto menu = Menu::create(menuItemNew, menuItemContinue, NULL);
    menu->alignItemsHorizontallyWithPadding(visibleSize.width * 0.1);
    menu->setPosition(startPos);
    this->addChild(menu);
    
    // BGM
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/DQ1.mp3");
    SimpleAudioEngine::getInstance()->playBackgroundMusic("res/DQ1.mp3", true);
    
    return true;
}
