#include "OptionLayer.h"
bool OptionLayer::init()
{
	if(!Layer::init()){
		return false;
	}
/*	auto musicBar = ControlSlider::create("blocks.png",
		"blocks.png",
		"CloseNormal.png");
	CCUserDefault::sharedUserDefault()->setIntegerForKey("integer", 10);  
	CCUserDefault::sharedUserDefault()->setBoolForKey("bool", true);  
	*/

	CCUserDefault::sharedUserDefault()->setBoolForKey("MUSIC_KEY",true);
	auto musicOn = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CloseNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CloseNormal.png")));
	auto musicOff = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CloseSelected.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CloseSelected.png"))); 
	auto music_value = MenuItemToggle::createWithTarget(this,menu_selector(OptionLayer::musicSet),musicOn,musicOff,NULL);
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("MUSIC_KEY"))
	{
		music_value->setSelectedIndex(1);
	}    else
	{
		music_value->setSelectedIndex(0);
	}
	music_value->setPosition(Point(100,200));
	auto menu = Menu::create(music_value, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	return true;
}
void OptionLayer::musicSet(Ref* obj){
	auto musicTemp =(MenuItemToggle*) obj;
			if(musicTemp->getSelectedIndex()==0){
				CCUserDefault::sharedUserDefault()->setBoolForKey("MUSIC_KEY",false);
			}
			else
			{
				CCUserDefault::sharedUserDefault()->setBoolForKey("MUSIC_KEY",true);
			}
			CCLOG("MUSIC_KEY=%d",CCUserDefault::sharedUserDefault()->getBoolForKey("MUSIC_KEY"));
}

