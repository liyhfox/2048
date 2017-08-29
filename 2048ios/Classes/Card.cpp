//
//  Card.cpp
//  2048
//
//  Created by L&L on 2017/3/27.
//
//

#include "Card.h"

USING_NS_CC;

CardSprite* CardSprite::createCardSprite(int number, int wight, int height, cocos2d::Point position)
{
    CardSprite *card = new CardSprite();
    if ( card && card->init())
    {
        card->autorelease();
        card->initCard(number, wight, height, position);
        return card;
    }
    CC_SAFE_DELETE(card);
    
    return nullptr;
}

CardSprite::~CardSprite()
{
    
}

bool CardSprite::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    
    return true;
}

void CardSprite::runNewNumberAction()
{
    auto action = ScaleBy::create(0.05, 0.99);
    runAction(Sequence::create(action, action->reverse(), nullptr));
}

int CardSprite::getNumber()
{
    return _number;
}

void CardSprite::setNumber(int num)
{
    _number = num;
    // update number
    if (num > 0)
    {
        _labelCardNumber->setString(__String::createWithFormat("%i", _number)->getCString());
    }
    else
    {
        _labelCardNumber->setString("");
    }
    
    // set number size
    if (num >= 1024)
    {
        _labelCardNumber->setSystemFontSize(_numberSize * 0.4);
    }
    else if (num >= 128)
    {
        _labelCardNumber->setSystemFontSize(_numberSize * 0.6);
    }
    else if (num >= 16)
    {
        _labelCardNumber->setSystemFontSize(_numberSize * 0.8);
    }
    else if (num >= 0)
    {
        _labelCardNumber->setSystemFontSize(_numberSize);
    }
    
    switch (_number) {
        case 0:
            _colorBackground->setColor(Color3B(200, 190, 180));
            break;
        case 2:
            _colorBackground->setColor(Color3B(240, 230, 220));
            break;
        case 4:
            _colorBackground->setColor(Color3B(240, 220, 200));
            break;
        case 8:
            _colorBackground->setColor(Color3B(240, 180, 120));
            break;
        case 16:
            _colorBackground->setColor(Color3B(240, 140, 90));
            break;
        case 32:
            _colorBackground->setColor(Color3B(240, 120, 90));
            break;
        case 64:
            _colorBackground->setColor(Color3B(240, 90, 60));
            break;
        case 128:
            _colorBackground->setColor(Color3B(240, 90, 60));
            break;
        case 256:
            _colorBackground->setColor(Color3B(240, 200, 70));
            break;
        case 512:
            _colorBackground->setColor(Color3B(240, 200, 70));
            break;
        case 1024:
            _colorBackground->setColor(Color3B(0, 130, 0));
            break;
        case 2048:
            _colorBackground->setColor(Color3B(0, 130, 0));
            break;
        default:
            break;
    }
}

void CardSprite::initCard(int number, int widht, int height, Point position)
{
    _number = number;
    _numberSize = widht;
    _colorBackground = LayerColor::create(Color4B(200, 190, 180, 255), widht * 0.9, height * 0.9);
 _colorBackground->setPosition(position);
    
    // if numer bigger than 0, show it
    if (number > 0)
    {
        _labelCardNumber = Label::createWithSystemFont(__String::createWithFormat("%i", number)->getCString(), "Consolas", 10);
    }
    else
    {
        _labelCardNumber = Label::createWithSystemFont("", "Consolas", 10);
    }
    _labelCardNumber->setPosition(Point(_colorBackground->getContentSize().width * 0.5, _colorBackground->getContentSize().height * 0.5));
    
    //_labelCardNumber->setPosition(position);
    _labelCardNumber->setTag(8);
    _colorBackground->addChild(_labelCardNumber);
    
    this->addChild(_colorBackground);
}
