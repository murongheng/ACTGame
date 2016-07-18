//
//  StateLayer.hpp
//  MyGame2-goodCode
//
//  Created by 千锋 on 16/3/22.
//
//

#ifndef StateLayer_hpp
#define StateLayer_hpp

#include <cocos2d.h>
USING_NS_CC;
#include "Global.hpp"
#include "HpShow.hpp"
class StateLayer : public Layer
{
public:
    StateLayer();
    ~StateLayer();
    virtual bool init();
    
    CREATE_FUNC(StateLayer);
    Label *label;
};

#endif /* StateLayer_hpp */
