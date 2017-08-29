//
//  SuccessLayer.cpp
//  2048
//
//  Created by L&L on 2017/4/11.
//
//

#include "SuccessLayer.hpp"

SuccessLayer* SuccessLayer::create(const cocos2d::Color4B &color)
{
    auto layer = new SuccessLayer();
    if (layer && layer->initWithColor(color)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool SuccessLayer::initWithColor(const cocos2d::Color4B &color)
{
    if (!LayerColor::initWithColor(color)) {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    Point centerPos = Point(winSize.width / 2, winSize.height / 2);
    auto winLabel = Label::createWithSystemFont("YOU WIN","Consolas", winSize.width * 0.1);
    winLabel->setPosition(centerPos);
    this->addChild(winLabel);
    
    scheduleOnce(SEL_SCHEDULE(&SuccessLayer::removeSuccessLayer), 2);
    
    return true;
}

void SuccessLayer::removeSuccessLayer()
{
    this->removeFromParent();
}
