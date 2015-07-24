#include "Mode.h"
#include "GameLayer.h"
Scene* Mode::createScene(){
	auto layer = Mode::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}
bool Mode::init(){
	if(!Layer::init()){
		return false;
	}
	auto menuItem = MenuItemFont::create("1",CC_CALLBACK_1(Mode::Level,this));
	menuItem->setTag(1);
	auto menu = Menu::create(menuItem,NULL);
	this->addChild(menu);
	return true;
}
void  Mode::Level(Ref *obj){
	auto menuitem = (MenuItem*) obj;
	int l = menuitem->getTag();
	this->delegator->selectLevel(l);
	this->removeFromParent();
}
