//
//  Hero.hpp
//  MyGame2-goodCode
//
//  Created by 千锋 on 16/3/22.
//
//

#ifndef Hero_hpp
#define Hero_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "Global.hpp"
#include "Role.hpp"
class Hero :public Role
{
public:
    Hero(void);
    ~Hero(void);
    virtual bool init();
    CREATE_FUNC(Hero);
    void onMove(Vec2 direction, float distance);
    void onStop();
    void onAttack(int number);
    void updateSelf();
    void attackCallBackAction(Node* pSender); //putonggongji
    void FontsCallBackAction(Node* pSender); //shuzidanchu
    void damageDisplay(int number, Vec2 point); //chanshengshanghaishuzi
   
};

#endif /* Hero_hpp */
