#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_
#include <cocos2d.h>
USING_NS_CC;
#include "GameLayer.hpp"
#include "StateLayer.hpp"
#include "OperateLayer.hpp"
class GameScene :public Scene
{
public:
	static cocos2d::Scene* createScene();
};

#endif