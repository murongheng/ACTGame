//
//  GaemStartScene.cpp
//  MyGame2-goodCode
//
//  Created by 千锋 on 16/3/22.
//
//

#include "GaemStartScene.hpp"
#include "GameStart.hpp"
Scene* GameStartScene::createScene()
{
    auto scene = Scene::create();
    auto gameStart = GameStart::create();
    gameStart->setPosition(0, 0);
    
    scene->addChild(gameStart);
    return scene;
}
