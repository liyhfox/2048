//
//  Card.h
//  2048
//
//  Created by L&L on 2017/3/22.
//
//

#ifndef __CARD_H__
#define __CARD_H__

#include "cocos2d.h"


class CardSprite : public cocos2d::Sprite
{
public:
    static CardSprite* createCardSprite(int number, int widht, int height, cocos2d::Point position);
    virtual bool init();
    CREATE_FUNC(CardSprite);
    ~CardSprite();
    
    int getNumber();
    void setNumber(int num);
    void runNewNumberAction();
    
private:
    void initCard(int number, int wight, int height, cocos2d::Point position);
    
private:
    int _number;
    
    int _numberSize;
    
    // Label
    cocos2d::Label *_labelCardNumber;
    
    // background
    cocos2d::LayerColor * _colorBackground;
};


#endif /* Card_h */
