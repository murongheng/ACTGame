//
//  Enemy.cpp
//  MyGame2-goodCode
//
//  Created by 千锋 on 16/3/20.
//
//

#include "Enemy.hpp"

Enemy::Enemy() : m_nextDicisionTime(0)
{

}

Enemy::~Enemy()
{
    
}

bool Enemy::init()
{
    bool ret = false;
    do {
        this->initWithSpriteFrameName("10009_walk_0000.png");
        
        Animation *idleAnim = this->createNomalAnimation("10009_walk_%04d.png", 1, 6);
        this->setIdleAction(RepeatForever::create(Animate::create(idleAnim)));
        //行走
        Animation *walkAnim = this->createNomalAnimation("10009_walk_%04d.png", 8, 8);
        this->setWalkAction(RepeatForever::create(Animate::create(walkAnim)));
        //攻击
        Animation *attackAnim = this->createAttackAnimation("10009_attack_%04d.png", 0, 8, 8);
        this->setNomalAttackA(Sequence::create(Animate::create(attackAnim), CallFuncN::create(CC_CALLBACK_1(Enemy::attackCallBackAction, this)), Role::createIdleCallbackFunc(),NULL));
        
        Animation *hurtAnim = this->createNomalAnimation("10009_hurt_%04d.png", 2, 4);
        this->setHurtAction(Sequence::create(Animate::create(hurtAnim), Role::createIdleCallbackFunc(), NULL));
        //死亡
        Animation *deadAnim = this->createNomalAnimation("10009_die_%04d.png", 8, 4);
        this->setDeadAction(Sequence::create(Animate::create(deadAnim), Blink::create(3, 9), FadeOut::create(0.5f), NULL));
        //获得精灵的矩形区域
        Size enemyShowSize = this->getSpriteFrame()->getRect().size;
        this->m_bodyBox = this->createBoundingBox(Vec2(0, 35), Size(60, 70));
        this->m_hitBox = this->createBoundingBox(Vec2(40, 35), Size(70, 70));
        ret = true;
    } while (0);
    return ret;
}

void Enemy::updateSelf()
{
    //对象坐标及body宽度
    this->execute(global->hero->getPosition() - Vec2(0, 25), global->hero->getBodyBox().actual.size.width);
    //如果在走，坐标移动
    if (this->getCurrActionState() == ACTION_STATE_WALK) {
        Vec2 location = this->getPosition();
        Vec2 direction = this->getMoveDirection();
        Vec2 expectP = location + direction;  //向量
        float mapTileHeight = global->tileMap->getTileSize().height;
        if (expectP.y < 38 || expectP.y > mapTileHeight * 3 + 30) {
            direction.y = 0;
        }
        float enemyfat = this->getBodyBox().actual.size.width / 2;
        if (expectP.x < enemyfat) {
            direction.x = 0;
        }
        //
        this->setFlippedX(direction.x < 0 ? true : false);
        this->setPosition(location + direction);
        this->updateBoxes();
        this->setLocalZOrder(this->getPositionY());
    }
    
    if (this->getCurrActionState() == ACTION_STATE_NOMAL_ATTACK_A) {
        this->runNomalAttackA();
    }
}
//执行延时，这是为了防止过快判断，判读的太过频繁不止给CPU压力，还会使效果出现问题。比如我们的敌人死追着Hero不放，撞了墙还在向着Hero的方向执行动画等。
void Enemy::execute(const cocos2d::Vec2 &target, float targetBodyWidth)
{
    if (m_nextDicisionTime == 0) { //延时到0执行下一个动作判定
        this->decide(target, targetBodyWidth);
    } else {
        -- m_nextDicisionTime;
    }
}

//FSM设定敌人的AI
/**
 Attack,攻击,每次攻击延时50
 
 Idle,发呆,延时随机一个0-1的数字*100
 
 Patrol,巡逻,延时时间也似随机出来的
 
 Pursuit,追击,当发现Hero追击的判断
 */
void Enemy::decide(const cocos2d::Vec2 &target, float targetBodyWidth)
{
//    log("%f", target.y);
    Vec2 location = this->getPosition() - Vec2(0, 35); //获得脚下坐标
//    log("%f", location.y);
    float distance = location.getDistance(target); //与对象body的距离
    distance = distance - targetBodyWidth / 2;
    
//    bool isFlippedX = this->isFlippedX();
//    bool isOnTargetLeft = (location.x < target.x ? true : false); //方向判定
//    if ((isFlippedX && isOnTargetLeft) || (!isFlippedX && !isOnTargetLeft)) {
//        this->m_aiState = CCRANDOM_0_1() > 0.5f ? AI_PATROL : AI_IDLE; //随机状态
//    } else {
        if (distance < m_eyeArea) { //在视野范围内
            this->m_aiState = (distance < m_attackArea)&&((fabsf(location.y - target.y ) < 10)) ? AI_ATTACK : AI_PURSUIT; //距离小于攻击范围，并且y坐标相差不超过15，则攻击
        } else {
            this->m_aiState = CCRANDOM_0_1() > 0.5f ? AI_PATROL : AI_IDLE;
        }
//    }
    switch (m_aiState) {
        case AI_ATTACK: {
            this->runNomalAttackA();
            this->m_nextDicisionTime = 50; //延时
        }
            break;
        case AI_IDLE: {
            this->runIdleAction();
            this->m_nextDicisionTime = CCRANDOM_0_1() * 100; //延时
        }
            break;
        case AI_PATROL: { //巡逻
            this->runWalkAction();
            //二维浮点坐标
            this->m_moveDirection.x = CCRANDOM_MINUS1_1();
            this->m_moveDirection.y = CCRANDOM_MINUS1_1();
            m_moveDirection.x = m_moveDirection.x > 0 ? (m_moveDirection.x + velocity.x) : (m_moveDirection.x - velocity.x);
            m_moveDirection.y = m_moveDirection.y > 0 ? (m_moveDirection.y + velocity.y) : (m_moveDirection.y - velocity.y);
            this->m_nextDicisionTime = CCRANDOM_0_1() * 100; //延时
        }
            break;
        case AI_PURSUIT: {
            this->runWalkAction();
            this->m_moveDirection = (target - location).getNormalized();
            this->setFlippedX(m_moveDirection.x < 0 ? true : false);
            m_moveDirection.x  = m_moveDirection.x > 0 ? (m_moveDirection.x + velocity.x) : (m_moveDirection.x - velocity.x);
            m_moveDirection.y  = m_moveDirection.y > 0 ? (m_moveDirection.y + velocity.y) : (m_moveDirection.y - velocity.y);
            this->m_nextDicisionTime = 10; //延时
        }
            break;
        default:
            break;
    }
}
void Enemy::attackCallBackAction(Node* pSender)
{
    Hero* t_hero = global->hero;
    Rect attackRect = m_hitBox.actual;
    Rect hurtRect = t_hero->getBodyBox().actual;
    //敌人攻击英雄
    if (attackRect.intersectsRect(hurtRect)) {
        t_hero->setAllowMove(false);
        int damage = this->getDamageStrenth();
        t_hero->runHurtAction();
        t_hero->setCurtLifeValue(t_hero->getCurtLifeValue() - damage);
    }
    if (t_hero->getCurtLifeValue() <= 0) {
        t_hero->runDeadAction();
//        m_attackArea = 0;
        t_hero->setBodyBox(createBoundingBox(Vec2::ZERO, Size::ZERO));
       
        t_hero->setPosition(Point(-10000, -10000));
    }
}


