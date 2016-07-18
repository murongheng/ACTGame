//
//  Global.hpp
//  MyGame2-goodCode
//
//  Created by 千锋 on 16/3/22.
//
//

#ifndef Global_hpp
#define Global_hpp

#include "cocos2d.h"
USING_NS_CC;

#include "Singleton.h"
#include "GameLayer.hpp"
#include "OperateLayer.hpp"
#include "StateLayer.hpp"


class GameLayer;
class OperateLayer;
class StateLayer;
class Hero;
class Enemy;


class Global :public Singleton<Global>
{
public:
    Global(void);
    ~Global(void);
    
    GameLayer *gameLayer;
    OperateLayer *operateLayer;
    StateLayer * stateLayer;
    Hero *hero;
    __Array *enemies;
    TMXTiledMap *tileMap;
    
//    Point tilePosFromLocation(Vec2 MovePoint, TMXTiledMap *map = NULL);
//    bool  tileAllowMove(Vec2 MovePoint);
};

#define global Global::instance()
#endif /* Global_hpp */
