#ifndef _BOOM_
#define _BOOM_
#include "cocos2d.h"
USING_NS_CC;
class Boom : public Node
{
public:
	int bx,by;
	CREATE_FUNC(Boom);
	bool init();
	static Boom* createBoom(int x, int y);
	void killSelf(Node *obj);
};
#endif // !_BOOM_
