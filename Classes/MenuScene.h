#ifndef _MENU_SCENE_
#define  _MENU_SCENE_
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocostudio;
using namespace ui;
class MenuScene:public Layer{
public:
	bool init();
	CREATE_FUNC(MenuScene);
	static Scene *createScene();
	void onClick(Ref* obj ,Widget::TouchEventType t);
	void menuItem(Ref *obj);
	void selectedItemEvent(Ref* pSender, ListViewEventType  type);
};
#endif