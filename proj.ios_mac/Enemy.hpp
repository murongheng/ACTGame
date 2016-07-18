//
//  Enemy.hpp
//  MyGame2-goodCode
//
//  Created by 千锋 on 16/3/22.
//
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "Global.hpp"
#include "Role.hpp"

typedef enum {
    AI_IDLE = 0,
    AI_PATROL,
    AI_ATTACK,
    AI_PURSUIT,
}AiState;

class Enemy : public Role
{
public:
    Enemy();
    ~Enemy();
    bool init();
    void updateSelf();
    CREATE_FUNC(Enemy);
    //
    CC_SYNTHESIZE(cocos2d::Vec2, m_moveDirection, MoveDirection);
    CC_SYNTHESIZE(float, m_eyeArea, EyeArea); //视野
    CC_SYNTHESIZE(float, m_attackArea, AttackArea); //攻击判定区
    CC_SYNTHESIZE(AiState, m_aiState, AiState);
    
    void attackCallBackAction(Node* pSender);
private:
    void decide(const cocos2d::Vec2& target, float targetBodyWidth);
    void execute(const cocos2d::Vec2& target, float targetBodyWidth);
    unsigned int m_nextDicisionTime;
};


#endif /* Enemy_hpp */
