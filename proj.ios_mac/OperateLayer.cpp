#include "OperateLayer.hpp"

using namespace std;

OperateLayer::OperateLayer()
{
	global->operateLayer=this;
}

OperateLayer::~OperateLayer()
{
}

bool OperateLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF( !Layer::init() );
        //operate set joystick
		auto m_pjoystick = Joystick::create();
		m_pjoystick->setJoystick(Vec2(50,50));
		this->addChild(m_pjoystick);

		auto visibleSize = Director::getInstance()->getVisibleSize();
//        log("%f", visibleSize.width);
		//create Icon
		auto attackItem = MenuItemImage::create("attackbuttonNormal.png","attackbuttonSelected.png",CC_CALLBACK_1(OperateLayer::attackButton,this));
        auto attackItem1 = MenuItemImage::create("SkillButton.png", "ttackbuttonSelected.png", CC_CALLBACK_1(OperateLayer::attackButton1, this));
        //set Scale
//		attackItem->setScale(1.5);
        //set position
		attackItem->setPosition(visibleSize.width - attackItem->getContentSize().width / 2 - 50, attackItem->getContentSize().height / 2 + 20);

        attackItem1->setPosition( attackItem->getPosition().x - 50, attackItem1->getContentSize().height / 2 + 20);
		auto menu = Menu::create(attackItem, attackItem1, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu,100);
        
		ret = true;
	} while(0);

	return ret;
}
void OperateLayer::attackButton1(Ref *pSender)
{
    global->hero->onAttack(2);
}
void OperateLayer::attackButton(Ref* pSender)
{
	global->hero->onAttack(1);
}