//
//  GameStart.hpp
//  MyGame2-goodCode
//
//  Created by 千锋 on 16/3/22.
//
//

#ifndef GameStart_hpp
#define GameStart_hpp

#include "cocos2d.h"
USING_NS_CC;
class GameStart : public Layer
{
public:
    GameStart();
    ~GameStart();
    virtual bool init();
    CREATE_FUNC(GameStart);
    void startButton(Ref* sender);
};


#endif /* GameStart_hpp */
