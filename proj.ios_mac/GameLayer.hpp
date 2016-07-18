//
//  GameLayer.hpp
//  MyGame2-goodCode
//
//  Created by 千锋 on 16/3/22.
//
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "MapLayer.hpp"
#include "Global.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"
class Hero;
class GameLayer : public Layer
{
public:
    GameLayer();
    ~GameLayer();
    virtual bool init();
    
    void addHero();
    //每次加入多个敌人,方便起见需要使用数组来实现它(链表更好)
    void addEnemies(int number);
    void update(float dt);
    void updateHero(float dt);
    void updateEnemies(float dt);
    __Array *m_pEnemies;
    CC_SYNTHESIZE_READONLY(Hero*, m_pHero, Hero);
    CREATE_FUNC(GameLayer);
//    void scoreDistplay(int number);
    CC_SYNTHESIZE(int,score,score);
    
//    Label *label;
//    void updateLabel(float dt);
private:
    Size _visibleSize;
    Vec2 _visibleOrigin;
    int _number;
};

#endif /* GameLayer_hpp */
