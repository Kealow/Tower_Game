#ifndef _GAMESCENE_
#define _GAMESCENE_
#include "cocos2d.h"
#include "Mode.h"
#include "GameLayer.h"
USING_NS_CC;
using namespace cocos2d;
class GameScene:public Scene{
public:
	GameLayer *gamelayer;
	Mode *mode;
	CREATE_FUNC(GameScene);
	bool init();
};
#endif