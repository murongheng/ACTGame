//
//  OperateLayer.hpp
//  MyGame2-goodCode
//
//  Created by 千锋 on 16/3/22.
//
//

#ifndef OperateLayer_hpp
#define OperateLayer_hpp

#include <cocos2d.h>
USING_NS_CC;
#include "Joystick.hpp"
class OperateLayer : public Layer
{
public:
    OperateLayer();
    ~OperateLayer();
    virtual bool init();
    
    void attackButton(Ref* pSender);
    void attackButton1(Ref* pSender);
    CREATE_FUNC(OperateLayer);
};

#endif /* OperateLayer_hpp */
