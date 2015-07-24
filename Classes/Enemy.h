#ifndef _ENEMY_
#define _ENEMY_
#include "cocos2d.h"
#include "TDPoint.h"
#include "ui/CocosGUI.h"
using namespace ui;
USING_NS_CC;
class Enemy : public Node{
public:
//  Vector<TDPoint *> nowPoint;
	int ex;
	int ey;
	int nowPointIndex;
	int type;
	int hp;
	int fullHp;
	int speed;
	CREATE_FUNC(Enemy);
	bool init();
	void MoveTo();
	static Enemy* createEnemy(int t,int h);
	void changeHp();
};
#endif