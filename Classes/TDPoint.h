#ifndef _TDPOINT_
#define _TDPOINT_
#include "cocos2d.h"
USING_NS_CC;
class TDPoint : public Ref{
public:
	int px;
	int py;
	static TDPoint* createPoint(int x,int y);
};
#endif;