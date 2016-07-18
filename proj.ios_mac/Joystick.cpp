#include "Joystick.hpp"
using namespace std;

Joystick::Joystick()
{
}

Joystick::~Joystick()
{
}

bool Joystick::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF( !Sprite::init() );
		m_pJoystickBg = Sprite::create("joystickBg.png");
		m_pJoystick = Sprite::create("joystick.png");
		this->addChild(m_pJoystickBg, 0);
		this->addChild(m_pJoystick, 1);
		this->hideJoystick();
		//this->showJoystick();
		m_pJoystickR= m_pJoystickBg->getContentSize().width / 2;
		m_pJoystickr= m_pJoystick->getContentSize().width / 2;

		auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(Joystick::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(Joystick::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(Joystick::onTouchesEnded, this);
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		ret = true;
	} while(0);

	return ret;
}

void Joystick::showJoystick()
{
	
	m_pJoystick->setVisible(true); 
	m_pJoystickBg->setVisible(true);
}

void Joystick::hideJoystick()
{
	
	//m_pJoystick->setPosition(m_pJoystickBg->getPosition());
	m_pJoystick->setVisible(false);
	//m_pJoystickBg->setVisible(false);
	m_pJoystickBg->setVisible(true);
}
//update joystick
void Joystick::updateJoystick(Touch* touch)
{
   //update the state of joystick by xiangliang
    Vec2 hit = touch->getLocation();
	float distance = start.getDistance(hit);
	Vec2 direction = (hit - start).getNormalized();
	
	if(distance < m_pJoystickR / 2)
	{
		m_pJoystick->setPosition(start + (direction * distance));
	}else if(distance > m_pJoystickR ) {
		m_pJoystick->setPosition(start + (direction * m_pJoystickr));
	}
//    else {
//		m_pJoystick->setPosition(start + (direction * m_pJoystickr / 2));
//	}

	global->hero->onMove(direction,distance);
}

//
void Joystick::onTouchesBegan(const vector<Touch*>& touches, Event *unused_event)
{
	std::vector<Touch*>::const_iterator touchIter = touches.begin();
	Touch* touch = (Touch*)(*touchIter);
	if(m_pJoystick->getBoundingBox().containsPoint(touch->getLocation()))
	{   //摇杆的二维包围盒是否包含接触点
		this->showJoystick();
		updateJoystick(touch);        
		CCLOG("***************");
		CCLOG("update touch:%f %f",touch->getLocation().x,touch->getLocation().y);

		return;
	}
}

void Joystick::onTouchesMoved(const vector<Touch*>& touches, Event *unused_event)
{
	
	std::vector<Touch*>::const_iterator touchIter = touches.begin();
	Touch* touch = (Touch*)(*touchIter);
	if(m_pJoystick->isVisible())
	{
		updateJoystick(touch);
		return;
	}
}

void Joystick::onTouchesEnded(const vector<Touch*>& touches, Event *unused_event)
{
	//m_pJoystick->runAction(MoveTo::create(0.08f,start));
	//m_pJoystick->setPosition(start);
	global->hero->onStop();
	this->hideJoystick();

}
void Joystick::setJoystick(Vec2 point)
{
	//jiang yaogan fangdao zuobiaoshang
	start =point;
	m_pJoystickBg->setPosition(start);
	m_pJoystick->setPosition(m_pJoystickBg->getPosition());
}
