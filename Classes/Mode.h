#ifndef _MODE_
#define _MODE_
#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;
class GameDelegate{
public:
	virtual void selectLevel(int l)=0;
};
class Mode :public Layer{
public:
	CREATE_FUNC(Mode);
	CC_SYNTHESIZE(GameDelegate*, delegator, Delegator);
	static Scene* createScene();
	bool init();
	void Level(Ref *obj);
};
#endif