#include "GameScene.h"
bool GameScene::init(){
	if(!Scene::init()){
		return false;
	}
	this->mode =Mode::create();
	this->gamelayer = GameLayer::getInstance();
	mode->setDelegator(gamelayer);
	this->addChild(gamelayer);
	this->addChild(mode);
}