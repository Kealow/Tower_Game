#include "MenuScene.h"
#include "GameScene.h"
#include "OptionLayer.h"
bool MenuScene::init(){
	if(!Layer::init()){
		return false;
	}
	//加载cocostudio文件
/*	auto node = GUIReader::getInstance()->widgetFromJsonFile("NewUI_1/NewUI_1.json");
	this->addChild(node); 
	Button *btn = (Button*)node->getChildByTag(4);
	btn->addTouchEventListener(CC_CALLBACK_2(MenuScene::onClick,this));

*/
	int w = Director::getInstance()->getVisibleSize().width;
	int h = Director::getInstance()->getVisibleSize().height;
	//加载图片帧缓存
	SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("play.plist","play.png");
	//创建菜单
/*	auto node = GUIReader::getInstance()->widgetFromJsonFile("TDMenu_1/TDMenu_1.json");
	this->addChild(node);
	auto start_btn = (Button*) node->getChildByName("star_Button");
	start_btn->addTouchEventListener(CC_CALLBACK_2(MenuScene::onClick,this));
	start_btn->setTag(1);
	auto option_btn =(Button*) node->getChildByName("option_Button");
	option_btn->addTouchEventListener(CC_CALLBACK_2(MenuScene::onClick,this));
	option_btn->setTag(2);
	auto quit_btn =(Button*) node->getChildByName("quit_Button");
	quit_btn->addTouchEventListener(CC_CALLBACK_2(MenuScene::onClick,this));
	quit_btn->setTag(3);*/
	//设置菜单项
	auto settingSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CloseNormal.png"));
	auto settingSprite_selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CloseNormal.png"));
	auto settingItem = MenuItemSprite::create(settingSprite,settingSprite_selected,CC_CALLBACK_1(MenuScene::menuItem,this));
	settingItem->setAnchorPoint(Point(1,0));
	settingItem->setPosition(Point(w,0));
	auto startSprite = Sprite::create("CloseNormal.png");
	auto startSprite_selected = Sprite::create("CloseNormal.png");
	auto startItem = MenuItemSprite::create(startSprite,startSprite_selected,CC_CALLBACK_1(MenuScene::menuItem,this));
	settingItem->setAnchorPoint(Point(1,0));
	settingItem->setTag(1);
	startItem->setPosition(Point(w/2,h/2));
	startItem->setTag(2);
	auto menu = Menu::create(settingItem,startItem,NULL);
	menu->setAnchorPoint(Point::ZERO);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	//设置ListView
	auto listView = ListView::create();
	listView->setDirection(SCROLLVIEW_DIR_VERTICAL);
	listView->setTouchEnabled(true);
	listView->setBounceEnabled(true);  // 反弹
	listView->setSize(Size(50, 100));
	listView->ignoreContentAdaptWithSize(false);
	listView->setAnchorPoint(Point(0.0, 0.0));
	listView->setPosition(Point(0, h / 4));
	listView->addEventListenerListView(this, SEL_ListViewEvent(&MenuScene::selectedItemEvent));

	this->addChild(listView);

	Button* default_button = Button::create("CloseNormal.png", "CloseNormal.png", "", UI_TEX_TYPE_PLIST);

	default_button->setName("Title Button");

	Layout* default_item = Layout::create();
	default_item->setTouchEnabled(true);
	default_item->setSize(default_button->getSize());
	default_button->setPosition(Point(default_item->getSize().width / 2.0f,
		default_item->getSize().height / 2.0f));
	default_item->addChild(default_button);

	// set model 将创建的模板设置为项目模板  
	listView->setItemModel(default_item);


	// 1
	Button* custom_buttonMZ = Button::create("CloseNormal.png", "CloseNormal.png", "", UI_TEX_TYPE_PLIST);
	custom_buttonMZ->setName("one Button");
	custom_buttonMZ->setScale9Enabled(true);
	custom_buttonMZ->setSize(default_button->getSize());
	Layout *custom_itemMZ = Layout::create();
	custom_itemMZ->setSize(custom_buttonMZ->getSize());
	custom_buttonMZ->setPosition(Point(custom_itemMZ->getSize().width / 2.0f, custom_itemMZ->getSize().height / 2.0f));
	custom_itemMZ->addChild(custom_buttonMZ);

	// 2
	Button* custom_buttonLion = Button::create("CloseNormal.png", "CloseNormal.png", "", UI_TEX_TYPE_PLIST);
	custom_buttonLion->setName("two Button");
	custom_buttonLion->setScale9Enabled(true);
	custom_buttonLion->setSize(default_button->getSize());
	Layout *custom_itemLion = Layout::create();
	custom_itemLion->setSize(custom_buttonLion->getSize());
	custom_buttonLion->setPosition(Point(custom_itemLion->getSize().width / 2.0f, custom_itemLion->getSize().height / 2.0f));
	custom_itemLion->addChild(custom_buttonLion);

	// 3
	Button* custom_buttonStone = Button::create("CloseNormal.png", "CloseNormal.png", "", UI_TEX_TYPE_PLIST);
	custom_buttonStone->setName("three Button");
	custom_buttonStone->setScale9Enabled(true);
	custom_buttonStone->setSize(default_button->getSize());
	Layout *custom_itemStone = Layout::create();
	custom_itemStone->setSize(custom_buttonStone->getSize());
	custom_buttonStone->setPosition(Point(custom_itemStone->getSize().width / 2.0f, custom_itemStone->getSize().height / 2.0f));
	custom_itemStone->addChild(custom_buttonStone);

	// 4
	Button* custom_buttonWood = Button::create("CloseNormal.png", "CloseNormal.png", "", UI_TEX_TYPE_PLIST);
	custom_buttonWood->setName("four Button");
	custom_buttonWood->setScale9Enabled(true);
	custom_buttonWood->setSize(default_button->getSize());
	Layout *custom_itemWood = Layout::create();
	custom_itemWood->setSize(custom_buttonWood->getSize());
	custom_buttonWood->setPosition(Point(custom_itemWood->getSize().width / 2.0f, custom_itemWood->getSize().height / 2.0f));
	custom_itemWood->addChild(custom_buttonWood);

	listView->pushBackCustomItem(custom_itemMZ);
	listView->pushBackCustomItem(custom_itemLion);
	listView->pushBackCustomItem(custom_itemStone);
	listView->pushBackCustomItem(custom_itemWood);

	return true;


}
Scene *MenuScene::createScene(){
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}
void MenuScene::menuItem(Ref* obj){
	auto it = (MenuItem*) obj;
	int t = it->getTag();
	switch (t)
	{
	case 1:{
		auto ol = OptionLayer::create();
		this->addChild(ol);
		break;
		   }
	case 2:{
		auto ns = GameScene::create();
		Director::getInstance()->replaceScene(ns);
		break;
		   }
	default:
		break;
	}
	


}
void MenuScene::onClick(Ref* obj ,Widget::TouchEventType t){
	auto btn = (Button*) obj;
	auto menuitem = btn->getTag();
	switch (menuitem)
	{
	case 1 :{
		CCLOG("pressed");
		auto s = GameScene::create();
		auto s2 = TransitionFlipX::create(1,s);
		Director::getInstance()->replaceScene(s2);}
		break;
	default:
		break;
	}
}
void MenuScene::selectedItemEvent(Ref* pSender, ListViewEventType  type){

}