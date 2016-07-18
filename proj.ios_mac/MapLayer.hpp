//
//  MpaLayer.hpp
//  MyGame2-goodCode
//
//  Created by 千锋 on 16/3/22.
//
//

#ifndef MpaLayer_hpp
#define MpaLayer_hpp

#include <cocos2d.h>
USING_NS_CC;
#include "Global.hpp"

class MapLayer : public Layer
{
public:
    MapLayer();
    ~MapLayer();
    virtual bool init();
    void update(float dt); //
    void setViewpointCenter(Point pos);
    CREATE_FUNC(MapLayer);
private:
    void initMapWithFile(const char * path);
};

#endif /* MpaLayer_hpp */
