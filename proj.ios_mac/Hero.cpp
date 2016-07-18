#include "Hero.hpp"

Hero::Hero(void)
{
	global->hero = this;
}
Hero::~Hero(void)
{
}

bool Hero::init(){
	bool ret = false;
	do 
	{
		this->initWithSpriteFrameName("20002_stand_0000.png");
		//this->setAnchorPoint(Vec2(0.48f, 0.13f));

		Animation *idleAnim = this->createNomalAnimation("20002_stand_%04d.png", 8, 5);
		this->setIdleAction(RepeatForever::create(Animate::create(idleAnim)));

		Animation *walkAnim = this->createNomalAnimation("20002_walk_%04d.png", 8, 12);
		this->setWalkAction(RepeatForever::create(Animate::create(walkAnim)));

		Animation *attackAnima1 = this->createAttackAnimation("20002_attack_1_%04d.png", 0, 4, 10);
		Animation *attackAnima2 = this->createAttackAnimation("20002_attack_1_%04d.png", 4, 6, 15);
		this->setNomalAttackA(Sequence::create(
			Animate::create(attackAnima1), 
			CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnima2),
			Role::createIdleCallbackFunc(),
			NULL));

		Animation *attackAnimb1 = this->createAttackAnimation("20002_attack_4_%04d.png", 0, 4, 10);
		Animation *attackAnimb2 = this->createAttackAnimation("20002_attack_4_%04d.png", 4, 8, 15);
		this->setNomalAttackB(Sequence::create(
			Animate::create(attackAnimb1), 
			CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnimb2),
			Role::createIdleCallbackFunc(),
			NULL));

		Animation *attackAnimc1 = this->createAttackAnimation("boy_attack_02_%02d.png", 0, 3, 10);
		Animation *attackAnimc2 = this->createAttackAnimation("boy_attack_02_%02d.png", 3, 6, 12);
		this->setNomalAttackC(Sequence::create(
			Animate::create(attackAnimc1), 
			//CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnimc2),
			Role::createIdleCallbackFunc(),
			NULL));

		Animation *chageAnim = this->createNomalAnimation("boy_change_attack_%02d.png", 4, 5);
		this->setChange(RepeatForever::create(Animate::create(chageAnim)));

		Animation *chageattAnim1= this->createAttackAnimation("boy_change_attack_%02d.png", 5, 7 , 10);
		Animation *chageattAnim2= this->createAttackAnimation("boy_change_attack_%02d.png", 7, 12 , 15);
		this->setChangeAttack(Sequence::create(
			Animate::create(chageattAnim1), 
			//CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(chageattAnim2),
			Role::createIdleCallbackFunc(),
			NULL));

		Animation *gurtAnim = this->createNomalAnimation("20002_hurt_%04d.png", 2, 4);
		this->setHurtAction(Sequence::create(
			Animate::create(gurtAnim), 
			Role::createIdleCallbackFunc(), 
			NULL));

		Animation *deadAnim = this->createNomalAnimation("boy_dead_%02d.png", 3, 6);
		this->setDeadAction(Sequence::create(
			Animate::create(deadAnim), 
			Blink::create(3, 9),
            FadeOut::create(0.5f),
			NULL));
 
		this->m_bodyBox = this->createBoundingBox(Vec2(0,30), Size(30,60));
		this->m_hitBox = this->createBoundingBox(Vec2(35,50), Size(80, 90));
		ret = true;
	} while(0);

	return ret;
}

void Hero::onMove(Vec2 direction, float distance)
{
	this->setFlippedX(direction.x < 0 ? true : false);
	this->runWalkAction();
	Vec2 velocity = direction * (distance < 33 ? 1 : 3);
	this->setVelocity(velocity);
}
void Hero::onStop()
{
	this->runIdleAction();
	this->setVelocity(Vec2::ZERO);
}
void Hero::onAttack(int number)
{
    switch (number) {
        case 1:
            this->runNomalAttackA();
            break;
        case 2:
            this->runNomalAttackB();
            break;
        case 3:
            this->runNomalAttackC();
            break;
        case 4:
            this->runNomalAttackD();
            break;
            
        default:
            break;
    }
	}

void Hero::updateSelf()
{
    //如果在走，位置移动
	if(this->getCurrActionState() == ACTION_STATE_WALK)
	{
        //hero no move out map 
		Vec2 currentP= this->getPosition();
//        log("%f", currentP.y);
        //velocity 向量
		Vec2 expectP = currentP + this->getVelocity();
		Vec2 actualP = expectP;
		float mapWidth = global->tileMap->getContentSize().width;
		float herofat = this->getBodyBox().actual.size.width / 2;
		float maptileHeight = global->tileMap->getTileSize().height;
        //no go to cube
		if(expectP.y < 25 || expectP.y > maptileHeight * 3 + 20)
		{
            actualP.y = currentP.y;
		}
		//no go out map
		if(expectP.x < herofat || expectP.x >= mapWidth - herofat)
		{
			actualP.x = currentP.x;
		}
		this->setPosition(actualP);
		this->setLocalZOrder( Director::getInstance()->getVisibleSize().height - this->getPositionY());
	}
}

void Hero::attackCallBackAction(cocos2d::Node *pSender)
{
    __Array *pEnemies = global->enemies;
    Ref *enemyObj = NULL;
    CCARRAY_FOREACH(pEnemies, enemyObj)
    {
        Enemy *pEnmey = (Enemy *)enemyObj;
        if (fabsf(this->getPosition().y - pEnmey->getPosition().y ) < 20) {
            Rect attackReck = m_hitBox.actual; //heroAttackArea
            Rect hurtReck = pEnmey->getBodyBox().actual; //enemyHurtArea
            if (attackReck.intersectsRect(hurtReck)) {
                pEnmey->setAllowMove(false);
                pEnmey->runHurtAction();
                int damage = random(this->getDamageStrenth() * 0.7, this->getDamageStrenth() * 1.3);
                damageDisplay(damage, pEnmey->getBodyBox().actual.origin);
                pEnmey->runHurtAction();
                pEnmey->setCurtLifeValue(pEnmey->getCurtLifeValue() - damage);
                if (pEnmey->getCurtLifeValue() <= 0) {
                    pEnmey->runDeadAction();
                    pEnmey->setBodyBox(createBoundingBox(Vec2::ZERO, Size::ZERO));
                }
            }
        }
    }
}

void Hero::FontsCallBackAction(cocos2d::Node *pSender)
{
    global->gameLayer->removeChild(pSender);
}

void Hero::damageDisplay(int number, cocos2d::Vec2 point)
{
    auto atLabel = Label::create();
    atLabel->setString(__String::createWithFormat("-%d", number)->getCString());
    atLabel->setSystemFontSize(20);

    atLabel->setColor(Color3B(255, 0, 0));
    atLabel->setPosition(point);
    global->gameLayer->addChild(atLabel, 200);
//    FiniteTimeAction *callFuncL = CallFuncN::create(atLabel, callfuncN_selector(Hero::FontsCallBackAction));
 
    FiniteTimeAction *callFuncL = CallFuncN::create(CC_CALLBACK_1(Hero::FontsCallBackAction, this));
    
    FiniteTimeAction *sequence = Sequence::create(
        ScaleTo::create(0.2f, 2.0f),
        MoveBy::create(0.2f, Vec2(0, 40)),
        FadeOut::create(0.5f),
        callFuncL,
        NULL);
    atLabel->runAction(sequence);
}


