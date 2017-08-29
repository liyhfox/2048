//
//  GameScene.cpp
//  2048
//
//  Created by L&L on 2016/12/26.
//
//

#include <stdio.h>
#include "GameScene.h"
#include "PauseLayer.hpp"
#include "GameOverLayer.hpp"
#include "Recognizer.hpp"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is a auto release object
    auto scene = Scene::create();
    
    // 'layer' is a auto release object
    auto layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

GameScene::~GameScene()
{
    // todo
    if (_recognizer != nullptr) {
        delete _recognizer;
    }
}

bool GameScene::init()
{
    
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto layerColorBG = LayerColor::create(Color4B(180, 170, 160, 255));
    this->addChild(layerColorBG);
    
    MenuItemFont::setFontName("Consolas");
    MenuItemFont::setFontSize(visibleSize.width * 0.09);
    auto menuItemPause = MenuItemFont::create("PAUSE", CC_CALLBACK_1(GameScene::onPause, this));
    
    auto menu = Menu::create(menuItemPause, NULL);
    this->addChild(menu);
    menu->setPosition(Point(visibleSize.width * 0.2, visibleSize.height * 0.9));
    
    // score
    auto cardNumberTitle = Label::createWithSystemFont("SCORE", "Consolas",visibleSize.width * 0.09);
    cardNumberTitle->setPosition(Point(visibleSize.width * 0.2, visibleSize.height * 0.8));
    this->addChild(cardNumberTitle);
    
    _score = 0;
    _cardNumberTTF = Label::createWithSystemFont("0", "Consolas", visibleSize.width * 0.09);
    _cardNumberTTF->setPosition(Point(visibleSize.width * 0.6, visibleSize.height * 0.8));
    this->addChild(_cardNumberTTF);
    
    /*// keyboard pressed event listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event *event) {
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
            {
                if (this->doUp())
                    this->doCheck();
            }
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            {
                if (this->doDown())
                    this->doCheck();
            }
                break;
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            {
                if (this->doLeft())
                    this->doCheck();
            }
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            {
                if (this->doRight())
                    this->doCheck();
            }
                break;
            default:
                log("not support keyboard pressed!!");
                break;
        }
    };
    keyboardListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event *event) { };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);*/
    
    this->setTouchEnabled(true);
    // touch event listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    touchListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    // touch recognizer
    _recognizer = new Recognizer();
    
    // create 4*4 cards
    createCardSprite(visibleSize);
    if (UserDefault::getInstance()->getBoolForKey("history")) {
        resumeStatus();
    }
    else
    {
        // init two numbers
        createCardNumber(false);
        createCardNumber(false);
    }
    
    return true;
}

void GameScene::onPause(Ref* pSender)
{
    PauseLayer *pauseLayer = PauseLayer::create(Color4B(0, 0, 0, 180));
    this->getParent()->addChild(pauseLayer);
    Director::getInstance()->pause();
}

void GameScene::createCardSprite(Size size)
{
    _cellSize = size.width * 0.9 * 0.25 * 0.99;
    _cellSpace = _cellSize * 0.005;
    
    // draw a 4 * 4 cells
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            CardSprite *card = CardSprite::createCardSprite(0, _cellSize, _cellSize, getPosition(i, j));
            _cardArray[i][j] = card;
            this->addChild(card);
            
        }
    }
}

void GameScene::createCardNumber(bool animation)
{
    // make sure random every time
    srand((unsigned int)time(0));
    
    while (1) {
        int i = CCRANDOM_0_1() * 4; // get random int from 0 to 3
        int j = CCRANDOM_0_1() * 4;
        
        log("[%d][%d]", i, j);
        
        if (_cardArray[i][j]->getNumber() == 0)
        {
            // rate of 2 and 4 is 9 : 1
            _cardArray[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
            if (animation) {
                _cardArray[i][j]->runNewNumberAction();
            }
            break;
        }
        
        if (!shouldCreateCardNumber())
        {
            break;
        }
        
    }
}

bool GameScene::shouldCreateCardNumber()
{
    bool isCreate = false;
    for (int i = 0; i < 4 ; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (0 == _cardArray[i][j]->getNumber())
            {
                isCreate = true;
                break;
            }
        }
    }
    
    return isCreate;
}

Point GameScene::getPosition(int x, int y)
{
    float pX = _cellSize / 3 + x * (_cellSize + _cellSpace);
    float pY = _cellSize / 3 + y * (_cellSize + _cellSpace) + _cellSize / 1.5;
    
    return Point(pX, pY);
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    cocos2d::Point point = touch->getLocation();
    _recognizer->BeginPoint(point);
    return true;
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    cocos2d::Point point = touch->getLocation();
    _recognizer->MovePoint(point);
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    cocos2d::Point point = touch->getLocation();
    Gesture ret = _recognizer->EndPoint(point);
    
    switch (ret) {
        case Gesture::_gestureUp:
        {
            if (this->doUp())
                this->doCheck();
        }
            break;
        case Gesture::_gestureDown:
        {
            if (this->doDown())
                this->doCheck();
        }
            break;
        case Gesture::_gestureLeft:
        {
            if (this->doLeft())
                this->doCheck();
        }
            break;
        case Gesture::_gestureRight:
        {
            if (this->doRight())
                this->doCheck();
        }
            break;
        default:
            log("not support touch!!");
            break;
    }
}

bool GameScene::doUp()
{
    bool isMove = false;
    for (int x = 0; x < 4; ++x)
    {
        for (int y = 3; y >= 0 ; --y)
        {
            for (int yd = y - 1; yd >= 0; --yd)
            {
                if (_cardArray[x][yd]->getNumber() > 0) // found valid card
                {
                    if (_cardArray[x][y]->getNumber() <= 0) // the above one is empty
                    {
                        _cardArray[x][y]->setNumber(_cardArray[x][yd]->getNumber());
                        _cardArray[x][yd]->setNumber(0);
                        ++y; // important!
                        isMove = true;
                    }
                    else if (_cardArray[x][yd]->getNumber() == _cardArray[x][y]->getNumber()) // above one equals to this one
                    {
                        _cardArray[x][y]->setNumber(_cardArray[x][yd]->getNumber() * 2);
                        _cardArray[x][yd]->setNumber(0);
                        
                        _score += _cardArray[x][y]->getNumber();
                        updateMaxNumber(x, y);
                        isMove = true;
                    }
                    
                    break;
                }
            }
        }
    }
    
    return isMove;
}

bool GameScene::doDown()
{
    bool isMove = false;
    
    for (int x = 0; x < 4; ++x)
    {
        for (int y = 0; y < 4; ++y)
        {
            for (int yu = y + 1; yu <= 3; ++yu)
            {
                if (_cardArray[x][yu]->getNumber() > 0)
                {
                    if (_cardArray[x][y]->getNumber() <= 0)
                    {
                        _cardArray[x][y]->setNumber(_cardArray[x][yu]->getNumber());
                        _cardArray[x][yu]->setNumber(0);
                        --y;
                        isMove = true;
                    }
                    else if (_cardArray[x][yu]->getNumber() == _cardArray[x][y]->getNumber())
                    {
                        _cardArray[x][y]->setNumber(_cardArray[x][yu]->getNumber() * 2);
                        _cardArray[x][yu]->setNumber(0);
                        _score += _cardArray[x][y]->getNumber();
                        updateMaxNumber(x, y);
                        isMove = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isMove;
}

bool GameScene::doLeft()
{
    bool isMove = false;
    
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4 ; ++x)
        {
            for (int xr = x + 1; xr <= 3; ++xr)
            {
                if (_cardArray[xr][y]->getNumber() > 0 )
                {
                    if (_cardArray[x][y]->getNumber() <= 0)
                    {
                        _cardArray[x][y]->setNumber(_cardArray[xr][y]->getNumber());
                        _cardArray[xr][y]->setNumber(0);
                        --x;
                        isMove = true;
                    }
                    else if (_cardArray[xr][y]->getNumber() == _cardArray[x][y]->getNumber())
                    {
                        _cardArray[x][y]->setNumber(_cardArray[xr][y]->getNumber() * 2);
                        _cardArray[xr][y]->setNumber(0);
                        _score += _cardArray[x][y]->getNumber();
                        updateMaxNumber(x, y);
                        isMove = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isMove;
}

bool GameScene::doRight()
{
    bool isMove = false;
    
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 3; x >= 0; --x)
        {
            for (int xl = x - 1; xl >= 0; --xl)
            {
                if (_cardArray[xl][y]->getNumber() > 0)
                {
                    if (_cardArray[x][y]->getNumber() <= 0)
                    {
                        _cardArray[x][y]->setNumber(_cardArray[xl][y]->getNumber());
                        _cardArray[xl][y]->setNumber(0);
                        ++x;
                        isMove = true;
                    }
                    else if (_cardArray[xl][y]->getNumber() == _cardArray[x][y]->getNumber())
                    {
                        _cardArray[x][y]->setNumber(_cardArray[xl][y]->getNumber() * 2);
                        _cardArray[xl][y]->setNumber(0);
                        _score += _cardArray[x][y]->getNumber();
                        updateMaxNumber(x, y);
                        isMove = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isMove;
}

bool GameScene::isGameOver()
{
    bool isGameOver = true;
    
    for (int x = 0; x < 4 && isGameOver; ++x)
    {
        for (int y = 0; y < 4 && isGameOver; ++y)
        {
            if ((_cardArray[x][y]->getNumber() == 0) ||
                (x < 3 && _cardArray[x][y]->getNumber() == _cardArray[x+1][y]->getNumber()) ||
                (x > 0 && _cardArray[x][y]->getNumber() == _cardArray[x-1][y]->getNumber()) ||
                (y < 3 && _cardArray[x][y]->getNumber() == _cardArray[x][y+1]->getNumber()) ||
                (y > 0 && _cardArray[x][y]->getNumber() == _cardArray[x][y-1]->getNumber()) )
            {
                isGameOver = false;
            }
        }
    }
    
    return isGameOver;
}

bool GameScene::isWin()
{
    bool res = getMaxNumber() >= 2048 ? true : false;
    if (res) {
        _needCheckWin = false;
    }
    return res;
}

void GameScene::doCheck()
{
    showScore();
    
    if (needCheckWin())
    {
        if (isWin()) {
            log("You win!");
            auto successLayer = SuccessLayer::create(Color4B(0, 0, 0, 180));
            this->getParent()->addChild(successLayer);
        }
    }

    if (shouldCreateCardNumber())
    {
        createCardNumber();
        saveStatus();
    }
    
    // check if game over after create a new card
    if (isGameOver())
    {
        log("game over!");
        GameOverLayer *gameOverLayer = GameOverLayer::create(Color4B(0, 0, 0, 180));
        this->getParent()->addChild(gameOverLayer);
    }
}

void GameScene::showScore()
{
    _cardNumberTTF->setString(__String::createWithFormat("%i", _score)->getCString());
};

void GameScene::saveStatus()
{
    char temp[10] = { 0 };
    // 4 * 4
    for (int i = 0; i < 4; ++i) {
        for (int j = 0 ; j < 4; ++j) {
            sprintf(temp, "%d%d", i, j);
            UserDefault::getInstance()->setIntegerForKey(temp, _cardArray[i][j]->getNumber());
        }
    }
    
    UserDefault::getInstance()->setIntegerForKey("score", _score);
    
    UserDefault::getInstance()->setBoolForKey("history", true);
}

void GameScene::resumeStatus()
{
    char temp[10] = { 0 };
    // 4 * 4
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            sprintf(temp, "%d%d", i, j);
            int number = UserDefault::getInstance()->getIntegerForKey(temp);
            _cardArray[i][j]->setNumber(number);
        }
    }
    
    _score = UserDefault::getInstance()->getIntegerForKey("score");
    showScore();
}
