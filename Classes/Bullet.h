#ifndef _BULLET_
#define _BULLET_
#include "cocos2d.h"
USING_NS_CC;
class Bullet:public Node
{
public:
	int bx,by;
	int objx,objy;
	int type;
	CREATE_FUNC(Bullet);
	bool init();
	static Bullet*createBullet(int t, int ang,int x,int y,int dx,int dy);
	void killMe();
};

#endif // !_BULLET_
