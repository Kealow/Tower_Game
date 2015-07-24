#include "GameLayer.h"
#include "Boom.h"
#include "MenuScene.h"
Vector<TDPoint*> GameLayer::allPoint;
Vector<Bullet *> GameLayer::allBullet;
Vector<Enemy *>  GameLayer::allEnemy;
Vector<TD *>GameLayer::allTD;
static GameLayer* gamelayer=nullptr;
GameLayer* GameLayer::getInstance(){
	if(!gamelayer){
		gamelayer = GameLayer::create();
	//	gamelayer->retain();
	}
	return gamelayer;
}
bool GameLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	//初始化关卡
//	this->nowLevel=1;
//	this->initLevel();
	//加入触摸
/*	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan=CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	listener->onTouchMoved=CC_CALLBACK_2(GameLayer::onTouchMoved,this);
	listener->onTouchEnded=CC_CALLBACK_2(GameLayer::onTouchEnded,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);*/
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}
void GameLayer::selectLevel(int l){
	this->nowLevel=l;
	initLevel();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan=CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	listener->onTouchMoved=CC_CALLBACK_2(GameLayer::onTouchMoved,this);
	listener->onTouchEnded=CC_CALLBACK_2(GameLayer::onTouchEnded,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
}

void GameLayer::initAllPoint(TMXTiledMap *m){
	ValueVector value;
	value=m->getObjectGroup("road")->getObjects();
	for(int i =0;i<value.size();i++){
		ValueMap vm = value.at(i).asValueMap();
		TDPoint* newp = TDPoint::createPoint(vm.at("x").asInt(),vm.at("y").asInt());
		allPoint.pushBack(newp);
	}
}
bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event){
	if (this->getChildByTag(1001)!=NULL)
	{
		this->removeChildByTag(1001);
	}
	if (this->getChildByTag(1002)!=NULL)
	{
		this->removeChildByTag(1002);
	}
	nowrow = (int)( touch->getLocation().x/32) ;
	nowcol =(int)(touch->getLocation().y/32);
	TMXTiledMap *map = (TMXTiledMap*)this->getChildByTag(888);
	int tid = map->getLayer("red")->getTileGIDAt(Vec2(nowrow,9-nowcol));
	CCLOG("r=%d,c=%d,id=%d",nowrow,nowcol,tid);
	bool canTouch = false;
	if(!map->getPropertiesForGID(tid).isNull()){
		auto tiledmap = map->getPropertiesForGID(tid).asValueMap();
		if(!tiledmap.empty()){
			canTouch=true;
		}
	}
	if(canTouch==true){
		if(mapdetail[nowrow][nowcol]==0&&this->getChildByTag(1002)==NULL){
		addTDSelect(nowrow,nowcol);
		CCLOG("Can Build");
		}
		if(mapdetail[nowrow][nowcol]!=0){
			//	canTouch=false;升级塔
			addTowerUp(nowrow,nowcol);
			CCLOG("UP or Sell");
		}
	}
	else
	{
		auto nosp = Sprite::createWithSpriteFrameName("CloseNormal.png");
//		auto nosp = Sprite::create("blocks.png",Rect(32,0,32,32));
		nosp->setAnchorPoint(Point::ZERO);
		nosp->setPosition(Vec2(nowrow*32,nowcol*32));
		this->addChild(nosp);
		nosp->runAction(Sequence::create(DelayTime::create(1),
			CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent,nosp)),
			NULL));
	}
	CCLOG("mapNum=%d",mapdetail[nowrow][nowcol]);
	return true;

}
void GameLayer::onTouchMoved(Touch *touch, Event *unused_event){

}
void GameLayer::onTouchEnded(Touch *touch, Event *unused_event){
}
void GameLayer::addTDSelect(int r,int c){
	//点击格子产生Image。菜单作为child加在Image上。
	auto Image = Sprite::create("blocks.png",Rect(32,0,32,32));
	int height =Image->getContentSize().height;
	int width = Image->getContentSize().width;
//	int height = 32;
//	int width = 32;
	auto item01 = Sprite::create("blocks.png",Rect(0,0,32,32));
	auto item01_select = Sprite::create("blocks.png",Rect(0,0,32,32));
	auto item02 = Sprite::create("blocks.png",Rect(32,0,32,32));
	auto item02_select = Sprite::create("blocks.png",Rect(32,0,32,32));
	auto item03 = Sprite::create("blocks.png",Rect(64,0,32,32));
	auto item03_select = Sprite::create("blocks.png",Rect(64,0,32,32));

	auto menuitem01 = MenuItemSprite::create(item01,item01_select,CC_CALLBACK_1(GameLayer::selectTD,this));
	auto menuitem02 =MenuItemSprite::create(item02,item02_select,CC_CALLBACK_1(GameLayer::selectTD,this));
	auto menuitem03 = MenuItemSprite::create(item03,item03_select,CC_CALLBACK_1(GameLayer::selectTD,this));
	menuitem01->_ID=1;
	menuitem02->_ID=2;
	menuitem03->_ID=3;
	menuitem01->setTag(10);
	menuitem02->setTag(11);
	menuitem03->setTag(12);

	menuitem01->setAnchorPoint(Vec2(1,0));
	menuitem02->setAnchorPoint(Vec2(0.5,0));
	menuitem03->setAnchorPoint(Vec2(0,0));

	auto menuTD = Menu::create(menuitem01,menuitem02,menuitem03,NULL);
	menuTD->setPosition(Point::ZERO);
	menuitem01->setPosition(Vec2(0,height));
	menuitem02->setPosition(Vec2(width/2,height));
	menuitem03->setPosition(Vec2(width,height));
	Image->addChild(menuTD);
	Image->setTag(1001);
	this->addChild(Image);
	Image->setAnchorPoint(Point::ZERO);
	Image->setPosition(r*32,c*32);



}
void GameLayer::addTowerUp(int r,int c){
	//升级菜单
	auto upLevel = Sprite::create("blocks.png",Rect(32,0,32,32));
	auto upLevel_select = Sprite::create("blocks.png",Rect(32,0,32,32));
	auto upItem = MenuItemSprite::create(upLevel,upLevel_select,CC_CALLBACK_1(GameLayer::upTower,this));
	//出售菜单
	auto sell = Sprite::create("blocks.png",Rect(32,0,32,32));
	auto sell_select = Sprite::create("blocks.png",Rect(32,0,32,32));
	auto sellItem = MenuItemSprite::create(sell,sell_select,CC_CALLBACK_1(GameLayer::sellTD,this));

	//菜单背景
	auto upMenu = Sprite::createWithSpriteFrameName("CloseNormal.png");
	int width = upMenu->getContentSize().width;
	int height = upMenu->getContentSize().height;
	upItem->setAnchorPoint(Point(1,0));
	sellItem->setAnchorPoint(Point(-1,0));
	auto menu = Menu::create(upItem,sellItem,NULL);
	menu->setPosition(Point::ZERO);
	upMenu->addChild(menu);
	this->addChild(upMenu);
	upMenu->setPosition(r*32,c*32);
	upMenu->setAnchorPoint(Point::ZERO);
	upMenu->setTag(1002);


}
//变卖塔
void GameLayer::sellTD(Ref *obj){
	auto oldTD = allTD.at(mapdetail[nowrow][nowcol]-1);
	this->money+=oldTD->price/2;
	oldTD->removeFromParent();
	allTD.eraseObject(oldTD);
	mapdetail[nowrow][nowcol]=0;
	this->getChildByTag(1002)->removeFromParent();
	auto label = (Label*) this->getChildByTag(2000)->getChildByTag(2002);
	label->setString(std::to_string(money));

}
//升级塔
void GameLayer::upTower(Ref *obj){
	int nowType = allTD.at(mapdetail[nowrow][nowcol]-1)->type;
	if(nowType<4){
	int upType = nowType+3;
	TD* utd = TD::createTD(upType,nowrow,nowcol);
	if(this->money>=utd->price){
	auto oldTD = allTD.at(mapdetail[nowrow][nowcol]-1);
	oldTD->removeFromParent();
	allTD.eraseObject(oldTD);
	this->addChild(utd);
	allTD.pushBack(utd);
	mapdetail[nowrow][nowcol]=allTD.getIndex(utd)+1;
	this->getChildByTag(1002)->removeFromParent();
	this->money-=utd->price;
	auto label = (Label*) this->getChildByTag(2000)->getChildByTag(2002);
	label->setString(std::to_string(money));
	}
	}
	else
	{

	}
}
void GameLayer::selectTD(Ref *obj){
	int type = obj->_ID;
	TD *td = TD::createTD(type,nowrow,nowcol);
	if(this->money>=td->price){
		this->money-=td->price;
		auto label = (Label*) this->getChildByTag(2000)->getChildByTag(2002);
		label->setString(std::to_string(money));
		this->addChild(td);
		allTD.pushBack(td);
		mapdetail[nowrow][nowcol]=allTD.getIndex(td)+1;
		this->getChildByTag(1001)->removeFromParent();
	}
	else{

	}

}
void GameLayer::update(float t){
//检测碰撞
	for(int i=0;i<GameLayer::allBullet.size();i++){
		Bullet *b = GameLayer::allBullet.at(i);
		Rect rb(b->getPosition().x,b->getPosition().y,10,10);
		for(int j = 0;j<GameLayer::allEnemy.size();j++){
			Enemy *e = GameLayer::allEnemy.at(j);
			Rect re(e->getPosition().x,e->getPosition().y,20,40);
			if(rb.intersectsRect(re)){
				e->hp--;
				e->changeHp();
				if(e->hp<0){
					//加钱
					this->money+=100;
					auto label = (Label*) this->getChildByTag(2000)->getChildByTag(2002);
					label->setString(std::to_string(money));
                     //怪物死亡爆炸
					Boom *boom =Boom::createBoom(e->getPosition().x,e->getPosition().y);
					this->addChild(boom);
				//	DelayTime::create(0.5);
                 //怪物消失
						e->removeFromParent();
					GameLayer::allEnemy.eraseObject(e);
				}
				//子弹消失
				b->removeFromParent();
				GameLayer::allBullet.eraseObject(b);
				i--;
			}
		}
	}
	//是否过关
    if(this->npcGroupIndex>=this->npcGroupCount&&this->allEnemy.size()==0){
		this->nowLevel++;
		if(this->nowLevel>2){
			this->unscheduleAllSelectors();
			auto scene = MenuScene::createScene();
			Director::getInstance()->replaceScene(TransitionFlipX::create(1,scene));
			return;
		}
		this->unscheduleUpdate();
		this->initLevel();
		

	}
}
void GameLayer::initLevel(){
	this->unscheduleAllSelectors();
	this->removeAllChildren();
	this->allPoint.clear();
	this->allBullet.clear();
	this->allEnemy.clear();
	this->allTD.clear();
	//初始化地图标记数组
  /*   mapdetail[10][15]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};*/
	for(int r=0 ;r<15;r++){
		for(int c = 0;c<10;c++){
			this->mapdetail[r][c]=0;
			CCLOG("r=%d,c=%d,%d",r,c,mapdetail[r][c]);
		}
	}
	//_________________________________________________________________________________
//	SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();帧缓存，读取plist代码
//	frameCache->addSpriteFramesWithFile("boy.plist","boy.png");
	ValueMap mapinfo = FileUtils::getInstance()->getValueMapFromFile(StringUtils::format("gamelevel00%d.plist",nowLevel));
	//获取背景信息
	std::string bgname = mapinfo["levelinfo"].asValueMap()["bgimg"].asString();
//	String bgname = mapinfo["levelinfo"].asValueMap()["bgimg"].asString();
	//背景
	auto sp = Sprite::create(bgname);
	this->addChild(sp);
	sp->setPosition(Vec2(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height/2));
	//加载地图
	std::string mapname = mapinfo["levelinfo"].asValueMap()["mapfile"].asString();
	auto map = TMXTiledMap::create(mapname);
	map->setTag(888);
	this->addChild(map);
	//加载路径点
	initAllPoint(map);
	//加载所有怪物
	this->schedule(schedule_selector(GameLayer::newEnemy),3);
	this->enemyCount=20;
	//加入金钱数目
	this->money = mapinfo["levelinfo"].asValueMap()["money"].asInt();
	auto * spritetool = Sprite::create("HelloWorld.png",Rect(0,0,480,50));
	spritetool->setAnchorPoint(Vec2(0.5,1));
	spritetool->setTag(2000);
	spritetool->setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2,Director::getInstance()->getVisibleSize().height));
	this->addChild(spritetool);
	auto moneylabel = Label::createWithBMFont("fonts/word.fnt","");
	moneylabel->setAnchorPoint(Vec2(0.5,1));
	moneylabel->setPosition(spritetool->getContentSize().width/2,spritetool->getContentSize().height/2);
	auto text = std::to_string(money);
	moneylabel->setString(text);
	moneylabel->setTag(2002);
	spritetool->addChild(moneylabel);
	//读取怪物的波数和每波的数目
	this->levelAllNpc = mapinfo["npcgroup"].asValueVector();
	this->npcGroupCount = levelAllNpc.size();
	this->npcGroupIndex = 0;
	this->npcNumberCount = levelAllNpc.at(npcGroupIndex).asValueVector().size();
	this->npcNumberIndex = 0;
    //怪物当前波数
	auto npcLabel = Label::createWithBMFont("fonts/word.fnt","");
	npcLabel->setAnchorPoint(Vec2(1,1));
	npcLabel->setPosition(spritetool->getContentSize().width*2,spritetool->getContentSize().height/2);
	auto npcText = std::to_string(npcGroupIndex);
	npcLabel->setString(npcText);
	npcLabel->setTag(2003);
	spritetool->addChild(npcLabel);
	//怪物总波数
	auto npcGroupLabel = Label::createWithBMFont("fonts/word.fnt","");
	npcGroupLabel->setAnchorPoint(Vec2(0,1));
	npcGroupLabel->setPosition(0,spritetool->getContentSize().height/2);
	auto npcGroupText = std::to_string(npcGroupCount);
	npcGroupLabel->setString(npcGroupText);
	npcGroupLabel->setTag(2003);
	spritetool->addChild(npcGroupLabel);
	//人物血条
	auto hpbar = LoadingBar::create("return.png");
	this->hp = 10;
	this->fullHp=10;
	hpbar->setTag(2005);
	hpbar->setPercent(100);
	hpbar->setPositionY(Director::getInstance()->getVisibleSize().height/2);
	hpbar->setScale(3);
	this->addChild(hpbar);
	//游戏逻辑
	this->scheduleUpdate();

}
void GameLayer::newEnemy(float t){
    //取出当前波当前个怪物的类型
	int type = 0;
	int h = 0;
	if(npcNumberIndex<npcNumberCount){
	t = levelAllNpc.at(npcGroupIndex).asValueVector().at(npcNumberIndex).asValueMap()["type"].asInt();
	h = levelAllNpc.at(npcGroupIndex).asValueVector().at(npcNumberIndex).asValueMap()["hp"].asInt();
	npcNumberIndex++;
	Enemy * e1 = Enemy::createEnemy(type ,h);
	this->addChild(e1);
	allEnemy.pushBack(e1);
	}
	else{
		if(allEnemy.empty()){//这一波的怪完全消失，下一波才出现
		npcNumberIndex=0;
		npcGroupIndex++;//下一波
		}
		if(npcGroupIndex>=levelAllNpc.size()){
			//停止产生怪物
			this->unschedule(schedule_selector(GameLayer::newEnemy));
			return;
		}
        npcNumberCount = levelAllNpc.at(npcGroupIndex).asValueVector().size();
	}
}
void GameLayer::changePlayerHp(){
	LoadingBar* hpbar = (LoadingBar*)this->getChildByTag(2005);
	if(this->hp>0){
	this->hp-=2;
	hpbar->setPercent(hp/(float)fullHp*100);
	}
	else{
		Director::getInstance()->replaceScene(MenuScene::createScene());
	}
}