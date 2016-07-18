#include "MapLayer.hpp"

MapLayer::MapLayer()
{
}
MapLayer::~MapLayer()
{
}

bool MapLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF( !Layer::init() );
		this->initMapWithFile("mymap.tmx");
		this->scheduleUpdate();
		ret = true;
	} while(0);

	return ret;
}
void MapLayer::initMapWithFile(const char * path)
{
	TMXTiledMap *TileMap = TMXTiledMap::create(path);
	TileMap->setPosition(0, 0);
	global->tileMap=TileMap;
	this->addChild(TileMap); 
}

void MapLayer::update(float dt)
{
    //position 相对于地图父节点
	this->setViewpointCenter(global->hero->getPosition());
}
//move map
void MapLayer::setViewpointCenter(Point pos)
{  
	Size winSize = Director::getInstance()->getWinSize();  
	auto _map = global->tileMap;

	int x = MAX(pos.x, winSize.width / 2);
    
	int y = MAX(pos.y, winSize.height / 2);

	x = MIN(x, (_map->getMapSize().width * _map->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_map->getMapSize().height * _map->getTileSize().height) - winSize.height/ 2);  
    //对象当前坐标
	Point actualPosition = Vec2(x, y); 
    //屏幕中点坐标
	Point centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
    //屏幕中的和所要移动到的目的地之间的距离
	Point viewPoint = centerOfView - actualPosition;
    //设定地图位置
	this->getParent()->setPosition(viewPoint);
    
}  
