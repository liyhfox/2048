//
//  Recognizer.cpp
//  2048
//
//  Created by L&L on 2017/5/3.
//
//

#include "Recognizer.hpp"

Recognizer& Recognizer::getInstance()
{
    static Recognizer instance;
    return instance;
}

void Recognizer::BeginPoint(cocos2d::Point point)
{
    _result = Gesture::_gestureBegin;
    _points.clear();
    _points.push_back(point);
}

void Recognizer::MovePoint(cocos2d::Point point)
{
    _points.push_back(point);
}

Gesture Recognizer::EndPoint(cocos2d::Point point)
{
    _points.push_back(point);
    
    if (_points.size() < 3) {
        return Gesture::_gestureError;
    }
    
    Gesture tmp_gesture = Gesture::_gestureError;
    double x = _points.back().x - _points.front().x;
    double y = _points.back().y - _points.front().y;
    
    if (abs(x) > abs(y)) {
        if (x > 0) {
            tmp_gesture = Gesture::_gestureRight;
        }
        else {
            tmp_gesture = Gesture::_gestureLeft;
        }
    }
    else {
        if (y > 0) {
            tmp_gesture = Gesture::_gestureUp;
        }
        else {
            tmp_gesture = Gesture::_gestureDown;
        }
    }
    
    if (_result == Gesture::_gestureBegin)
        _result = tmp_gesture;
    
    if (_result != tmp_gesture)
        _result = Gesture::_gestureError;
    
    return _result;
}
