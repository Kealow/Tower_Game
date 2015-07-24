#ifndef _OPTIONLAYER_
#define _OPTIONLAYER_
#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;
//using namespace cocos2d::extension;

class OptionLayer:public Layer
{
public:
	CREATE_FUNC(OptionLayer)
	bool init();
	void musicSet(Ref* obj);
};
#endif