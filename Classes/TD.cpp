#include "TD.h"
#include "GameLayer.h"
TD * TD::createTD(int t,int r,int c){
	TD * td = TD::create();
	if(t==1){
	td->price = 200;
	//底座与上端2种贴图。后面达到上方旋转攻击效果
	auto base  = Sprite::create("blocks.png",Rect(0,0,32,32));
	base->setAnchorPoint(Point::ZERO);
	td->setPosition(Vec2(r*32,c*32));
	base->setTag(10);
	td->addChild(base);
	auto top = Sprite::create("CloseNormal.png");
//	top->setAnchorPoint(Point::ZERO);
	top->setTag(11);
	base->addChild(top);
	//为以后升级设置属性；
	td->type = t;
	td->trow = r;
	td->tcol = c;
	td->range = 32*3;
	td->tx=td->getPositionX();
	td->ty=td->getPositionY();
	td->schedule(schedule_selector(TD::moveAndShot),0.5);
	}
	if(t==4){
		td->price = 200;
		//底座与上端2种贴图。后面达到上方旋转攻击效果
		auto base  = Sprite::create("blocks.png",Rect(32,0,32,32));
		base->setAnchorPoint(Point::ZERO);
		td->setPosition(Vec2(r*32,c*32));
		base->setTag(10);
		td->addChild(base);
		auto top = Sprite::create("CloseNormal.png");
		//	top->setAnchorPoint(Point::ZERO);
		top->setTag(11);
		base->addChild(top);
		//为以后升级设置属性；
		td->type = t;
		td->trow = r;
		td->tcol = c;
		td->range = 32*3;
		td->tx=td->getPositionX();
		td->ty=td->getPositionY();
		td->schedule(schedule_selector(TD::moveAndShot),0.5);
	}


	return td;
}
bool TD::init(){
	if(!Node::init()){
		return false;
	}
	return true;
}
void TD::moveAndShot(float t){
	if(GameLayer::allEnemy.size()==0){
		return;
	}
	//检测最近目标
	int index = 0;
	int min = GameLayer::allEnemy.at(0)->getPosition().getDistance(this->getPosition());
	for(int i=0;i<GameLayer::allEnemy.size();i++){
			int distance = GameLayer::allEnemy.at(i)->getPosition().getDistance(this->getPosition());
			if(distance<min){
				index = i;
				min=distance;
			}
	}
	//计算角度
	Vec2 rotaVec = GameLayer::allEnemy.at(index)->getPosition() - this->getPosition();
	this->dx = GameLayer::allEnemy.at(index)->getPositionX();
	this->dy = GameLayer::allEnemy.at(index)->getPositionY();
	float rotation = rotaVec.getAngle();
	float ang = CC_RADIANS_TO_DEGREES(-1*rotation);
	this->angle = ang;
	float speed = 0.5/M_PI;
	float rotaDuratime = fabs(rotation*speed);
	this->getChildByTag(10)->getChildByTag(11)->runAction(Sequence::create(RotateTo::create(rotaDuratime,ang),
		CallFunc::create(CC_CALLBACK_0(TD::fire,this)),
		NULL));

}

void TD::fire(){
	if(Vec2(this->tx,this->ty).getDistance(Vec2(dx,dy))<this->range){
	Bullet * b = Bullet::createBullet(1,angle,this->tx,this->ty,dx,dy);
	GameLayer::allBullet.pushBack(b);
	this->getParent()->addChild(b);
	}
}