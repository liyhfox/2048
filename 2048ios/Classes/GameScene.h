//
//  GameScene.h
//  2048
//
//  Created by L&L on 2016/12/26.
//
//

#ifndef GameScene_h
#define GameScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "Card.h"
#include "SuccessLayer.hpp"
#include "Recognizer.hpp"


class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    ~GameScene();
    
private:
    void onPause(Ref* pSender);
    
    void createCardSprite(cocos2d::Size size);
    
    void createCardNumber(bool animation = true);
    
    bool shouldCreateCardNumber();
    
    cocos2d::Point getPosition(int x, int y);
    
    // Touch function
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    
    // move
    bool doUp();
    
    bool doDown();
    
    bool doLeft();
    
    bool doRight();
    
    // check game status
    bool isGameOver();
    
    bool isWin();
    
    void doCheck();
    
    void showScore();
    
    void saveStatus();
    
    void resumeStatus();
    
    void updateMaxNumber(int x, int y)
    {
        _maxNumber = _maxNumber > _cardArray[x][y]->getNumber() ? _maxNumber : _cardArray[x][y]->getNumber();
    };
    
    int getMaxNumber() { return _maxNumber; }
    
    bool needCheckWin() { return _needCheckWin; };
    
private:
    int _score;
    
    int _maxNumber = 0;
    
    int _cellSize = 0;
    int _cellSpace = 0;
    
    bool _needCheckWin = true;
    
    CardSprite *_cardArray[4][4];
    
    // label to show score
    cocos2d::Label *_cardNumberTTF;
    
    Recognizer *_recognizer;
};


#endif /* GameScene_h */
