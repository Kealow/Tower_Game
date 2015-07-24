#include "Bullet.h"
#include "GameLayer.h"
bool Bullet::init(){
	if(!Node::init()){
		return false;
	}

	return true;
}
Bullet*Bullet::createBullet(int t,int ang, int x,int y,int dx,int dy){
	Bullet * newb  = Bullet::create();
	newb->setTag(1);
	if(t==1){
		int speed = 20;
		newb->setPosition(x,y);
		newb->setRotation(ang);
		auto bl =Sprite::create("CloseNormal.png",Rect(10,10,10,10));
		newb->addChild(bl);
		newb->objx = dx;
		newb->objy = dy;
		int  distance= Vec2(x,y).getDistance(Vec2(dx,dy));
		int time = distance/speed;
		auto act1 =MoveTo::create(time,Vec2(dx,dy));
		auto act2 =CallFunc::create(CC_CALLBACK_0(Bullet::killMe,newb));
		newb->runAction(Sequence::create(act1,act2,NULL));

	}

	return newb;
}
void Bullet::killMe(){
	this->removeFromParent();
	GameLayer::allBullet.eraseObject(this);

}