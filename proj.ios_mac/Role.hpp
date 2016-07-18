//
//  Role.hpp
//  MyGame2-goodCode
//
//  Created by 千锋 on 16/3/22.
//
//

#ifndef Role_hpp
#define Role_hpp

#include "cocos2d.h"
USING_NS_CC;
typedef struct _BoundingBox
{
    Rect actual;
    Rect original;
}BoundingBox;
typedef enum {
    ACTION_STATE_NONE = 0,
    ACTION_STATE_IDLE,
    ACTION_STATE_WALK,
    ACTION_STATE_RUN,
    ACTION_STATE_JUMP,
    ACTION_STATE_NOMAL_ATTACK_A,
    ACTION_STATE_NOMAL_ATTACK_B,
    ACTION_STATE_NOMAL_ATTACK_C,
    ACTION_STATE_NOMAL_ATTACK_D,
    ACTION_STATE_CHANGE,
    ACTION_STATE_CHANGE_ATTACK,
    ACTION_STATE_RUSH_ATTACK,
    ACTION_STATE_JUMP_ATTACK_A,
    ACTION_STATE_JUMP_ATTACK_B,
    ACTION_STATE_SKILL_ATTACK_A,
    ACTION_STATE_SKILL_ATTACK_B,
    ACTION_STATE_SKILL_ATTACK_C,
    ACTION_STATE_HURT,
    ACTION_STATE_DEAD
}ActionState;

class Role :public Sprite
{
public:
    Role(void);
    ~Role(void);
    
    CC_SYNTHESIZE(float,curtLifevalue,CurtLifeValue);
    CC_SYNTHESIZE(float,sumLifevalue,SumLifeValue);
    CC_SYNTHESIZE(float,damagestrenth,DamageStrenth);
    CC_SYNTHESIZE(Vec2, velocity, Velocity);
    
    CC_SYNTHESIZE(bool, allowmove, AllowMove);
    CC_SYNTHESIZE(ActionState,currActionState,CurrActionState);
    CC_SYNTHESIZE_RETAIN(Action*, m_pidleaction, IdleAction);
    CC_SYNTHESIZE_RETAIN(Action*, m_pwalkaction, WalkAction);
    CC_SYNTHESIZE_RETAIN(Action*, m_prunaction,
                         RunAction );
    CC_SYNTHESIZE_RETAIN(Action*, m_pjumpaction, JumpAction);
    
    
    CC_SYNTHESIZE_RETAIN(Action*, m_pnomalattacka, NomalAttackA);
    CC_SYNTHESIZE_RETAIN(Action*, m_pnomalattackb, NomalAttackB);
    CC_SYNTHESIZE_RETAIN(Action*, m_pnomalattackc, NomalAttackC);
    CC_SYNTHESIZE_RETAIN(Action*, m_pnomalattackd, NomalAttackD);
    CC_SYNTHESIZE_RETAIN(Action*, m_pchange,  Change);
    CC_SYNTHESIZE_RETAIN(Action*, m_pchangeattack,  ChangeAttack);
    
    CC_SYNTHESIZE_RETAIN(Action*, m_prushattack,   RushAttack  );
    CC_SYNTHESIZE_RETAIN(Action*, m_pjumpattacka,  JumpAttackA );
    CC_SYNTHESIZE_RETAIN(Action*, m_pjumpattackb,  JumpAttackb );
    CC_SYNTHESIZE_RETAIN(Action*, m_pskillattacka, SkillAttackA);
    CC_SYNTHESIZE_RETAIN(Action*, m_pskillattackb, SkillAttackB);
    CC_SYNTHESIZE_RETAIN(Action*, m_pskillattackc, SkillAttackC);
    
    CC_SYNTHESIZE_RETAIN(Action*, m_phurtaction, HurtAction);
    CC_SYNTHESIZE_RETAIN(Action*, m_pdeadaction, DeadAction);
    
    void callBackAction(Node* pSender);
    
    
    virtual void runIdleAction();
    virtual void runWalkAction();
    virtual void runRunAction();
    virtual void runJumpAction();
    virtual void runNomalAttackA();
    virtual void runNomalAttackB();
    virtual void runNomalAttackC();
    virtual void runNomalAttackD();
    virtual void runChange();
    virtual void runChangeAttack();
    virtual void runRushAttack();
    virtual void runJumpAttackA();
    virtual void runJumpAttackB();
    virtual void runSkillAttackA();
    virtual void runSkillAttackB();
    virtual void runSkillAttackC();
    virtual void runHurtAction();
    virtual void runDeadAction();
    CallFunc* createIdleCallbackFunc();
    
    BoundingBox createBoundingBox(Vec2 origin,Size size);
    CC_SYNTHESIZE(BoundingBox, m_bodyBox, BodyBox);
    CC_SYNTHESIZE(BoundingBox, m_hitBox, HitBox);
    virtual void setPosition(const Vec2 &position);
    
    void updateBoxes();
protected:
    static Animation* createNomalAnimation(const char* formatStr, int frameCount, int fps);
    static Animation* createAttackAnimation(const char* formatStr, int frameCountBegan, int frameCountEnd,int fps);
private:
    bool changeState(ActionState actionState);
    ActionState proActionState;
};

#endif /* Role_hpp */
