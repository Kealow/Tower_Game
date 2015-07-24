#ifndef _TD_
#define _TD_
#include "cocos2d.h"
USING_NS_CC;
class TD:public Node
{
public:
	int tx,ty;
	int trow,tcol;
	int type;
	int price;
	int act;
	int angle;
	int dx,dy;
	int range;
	CREATE_FUNC(TD);
	static TD * createTD(int t,int r,int c);
	bool init();
	void moveAndShot(float t);
	void fire();

};
#endif
