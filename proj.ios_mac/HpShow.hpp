//
//  HpShow.hpp
//  MyGame2-goodCode
//
//  Created by 千锋 on 16/3/22.
//
//

#ifndef HpShow_hpp
#define HpShow_hpp

#include "cocos2d.h"
#include "Global.hpp"
USING_NS_CC;

class HpShow : public Node
{
public:
    HpShow();
    ~HpShow();
    virtual bool init();
    void update(float dt);
    CREATE_FUNC(HpShow);
    
    Label *label;
private:
    ProgressTimer* m_preal;
};


#endif /* HpShow_hpp */
