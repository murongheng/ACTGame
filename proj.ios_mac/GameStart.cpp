//
//  GameStart.cpp
//  MyGame2-goodCode
//
//  Created by 千锋 on 16/3/22.
//
//

#include "GameStart.hpp"
#include "GameScene.h"
GameStart::GameStart()
{
    
}
GameStart::~GameStart()
{
    
}

bool GameStart::init()
{
    bool ret = false;
    do {
        CC_BREAK_IF( !Layer::init() );
//      auto visibleSize = Director::getInstance()->getVisibleSize();
        auto sprite = Sprite::create("118.jpg");
        sprite->setPosition(240, 160);
        this->addChild(sprite);
        MenuItemImage *start = MenuItemImage::create("start.png", "start.png", CC_CALLBACK_1(GameStart::startButton, this));
        start->setPosition(160, 60);
        auto menu = Menu::create(start, NULL);
        this->addChild(menu);
       
        ret = true;
    } while (0);
    return ret;
}

void GameStart::startButton(Ref *sender)
{
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, GameScene::createScene()));
}