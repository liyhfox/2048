//
//  Recognizer.hpp
//  2048
//
//  Created by L&L on 2017/5/3.
//
//

#ifndef Recognizer_hpp
#define Recognizer_hpp

#include <stdio.h>
#include <vector>
#include "cocos2d.h"

enum class Gesture {
    _gestureRight,
    _gestureLeft,
    _gestureUp,
    _gestureDown,
    _gestureError,
    _gestureBegin,
};

class Recognizer
{
public:
    Recognizer& getInstance();
    
    Recognizer(const Recognizer&) = delete;
    Recognizer& operator=(const Recognizer&) = delete;
    
    void BeginPoint(cocos2d::Point point);
    void MovePoint(cocos2d::Point point);
    Gesture EndPoint(cocos2d::Point point);
    
    Recognizer() {};
    ~Recognizer() {};
    
private:
    std::vector<cocos2d::Point> _points;
    Gesture _result;
};

#endif /* Recognizer_hpp */
