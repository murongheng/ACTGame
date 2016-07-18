#include "GameLayer.hpp"

GameLayer::GameLayer()
{
	global->gameLayer=this;
}
GameLayer::~GameLayer()
{
}
bool GameLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF( !Layer::init());
		_visibleSize  = Director::getInstance()->getVisibleSize();
		_visibleOrigin = Director::getInstance()->getVisibleOrigin();
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Boy.plist","Boy.pvr.ccz");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("20002_attack_1.plist");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("20002_hurt.plist");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("20002_walk.plist");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("20002_stand.plist");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("20002_attack_4.plist");
        //hero1
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("20001_attack_2.plist");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("20001_hurt.plist");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("20001_walk.plist");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("20001_stand.plist");
        
		this->addHero();
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy.plist","enemy.pvr.ccz");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("10009_walk.plist");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("10009_attack.plist");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("10009_die.plist");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("10009_hurt.plist");
        
        this->addEnemies(5);
		auto map = MapLayer::create();
        this->setscore(0);
        this->addChild(map,-100);
		this->scheduleUpdate();

        
        
		ret = true;
	} while(0);
	return ret;
}
//
void GameLayer::update(float dt)
{
	this->updateHero(dt);
    this->updateEnemies(dt);
//    this->updateLabel(dt);
}
//
void GameLayer::updateHero(float dt)
{
	m_pHero->updateSelf();
}

void GameLayer::addHero()
{
    //创建hero
	m_pHero = Hero::create();
	m_pHero->setPosition(_visibleOrigin + Vec2(100, 50));
    m_pHero->setScale(0.5, 0.5);
	m_pHero->runIdleAction();
	//设置属性
	m_pHero->setDamageStrenth(25);
	m_pHero->setSumLifeValue(200);
	m_pHero->setCurtLifeValue(m_pHero->getSumLifeValue());

	m_pHero->setLocalZOrder(_visibleSize.height - m_pHero->getPositionY());
	this->addChild(m_pHero);
}

void GameLayer::addEnemies(int number)
{
    m_pEnemies = __Array::createWithCapacity(number);
    m_pEnemies->retain();
    for (int i = 0; i < number; ++i) {
        Enemy *pEnemy = Enemy::create();
        pEnemy->setScale(0.5, 0.5);
        pEnemy->setPosition(Vec2(random(_visibleSize.width / 2, _visibleSize.width), 70));
        pEnemy->runIdleAction();
        pEnemy->setLocalZOrder(_visibleSize.height - pEnemy->getPositionY());
        pEnemy->setVelocity(Vec2(0.5f, 0.5f));
        pEnemy->setEyeArea(300);
        pEnemy->setAttackArea(60);
        pEnemy->setDamageStrenth(5);
        pEnemy->setSumLifeValue(100);
        pEnemy->setCurtLifeValue(m_pHero->getSumLifeValue());
        m_pEnemies->addObject(pEnemy);
        this->addChild(pEnemy, 0);
    }
    global->enemies = m_pEnemies;
}

void GameLayer::updateEnemies(float dt)
{
    static int i = 0;
    Ref *Obj = NULL;
    Vec2 distance = Vec2::ZERO;
    auto enemyNumber = 0;
    CCARRAY_FOREACH(m_pEnemies, Obj)//bianli
    {
        Enemy *pEnemy = (Enemy*)Obj;
        pEnemy->updateSelf();//zhigengxinzhuangtai
        enemyNumber++;
        if(pEnemy->getDeadAction()->isDone()) {
            m_pEnemies->removeObject(pEnemy);
//            _number++;
//            log("%d", _number);
            
        }
    }
//    log("%d", enemyNumber);
    if (enemyNumber == 0) {
        this->addEnemies(5);
        i += 5;
        this->setscore(i);
//        this->scoreDistplay(i);
//        this->setscore(i);
    }
}


//void GameLayer::scoreDistplay(int number)
//{
//    label->setString(__String::createWithFormat("得分: %d", number)->getCString());
//
//}
