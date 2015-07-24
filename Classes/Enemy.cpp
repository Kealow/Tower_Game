#include "Enemy.h"
#include "GameLayer.h"
bool Enemy::init(){
	if(!Node::init()){
		return false;
	}
	return true;
};
void Enemy::MoveTo(){
	this->nowPointIndex++;
	if(nowPointIndex>GameLayer::allPoint.size()-1){
		//掉血
		//因为changeHP不是静态函数。所以不能直接类名引用。而因为Enemy的父节点是GameLayer。所以应先创建对象再进行调用。
	//	GameLayer * gs = (GameLayer *)this->getParent();
	//	gs->changePlayerHp();
		GameLayer::getInstance()->changePlayerHp();
		//死怪
		GameLayer::allEnemy.eraseObject(this);
		this->removeFromParent();
		return;
	}
	int x = GameLayer::allPoint.at(nowPointIndex)->px;//下一个点的坐标
	int y = GameLayer::allPoint.at(nowPointIndex)->py;
//	int distance = sqrt((x-this->ex)*(x-this->ex)+(y-this->ey)*(y-this->ey));
	int distance = Vec2(x,y).getDistance(Vec2(ex,ey));
	int time = distance/this->speed;
	this->ex=x;//点的数据传递下去
	this->ey=y;
	auto act1 = MoveTo::create(time,Vec2(x,y));
	auto act2 = CallFunc::create(CC_CALLBACK_0(Enemy::MoveTo,this));
	this->runAction(Sequence::create(act1,act2,NULL));
};
Enemy* Enemy::createEnemy(int t,int h){
	Enemy * newE = Enemy::create();
	newE->type=t;
		Vector<SpriteFrame*> allf;
		
			SpriteFrame * sf = SpriteFrame::create("CloseNormal.png",Rect(0,0,20,40));
			allf.pushBack(sf);
			SpriteFrame * sf1 = SpriteFrame::create("CloseNormal.png",Rect(20,0,20,40));
			allf.pushBack(sf1);


		newE->speed=30;
		newE->hp=h;
		newE->fullHp=h;
		Animation *animation = Animation::createWithSpriteFrames(allf,0.3f);
		Animate * ani = Animate::create(animation);
		
		Sprite *sp =Sprite::create();
		sp->setOpacity(0);//设置精灵透明
		sp->setTag(100);
		sp->runAction(RepeatForever::create(ani));
		newE->addChild(sp);
		//设置血量
		auto hpbar = LoadingBar::create("return.png");
		hpbar->setTag(1000);
		hpbar->setPercent(100);
		hpbar->setPositionY(32);
		newE->addChild(hpbar,1);
	//移动怪物
		int x = GameLayer::allPoint.at(0)->px;
		int y = GameLayer::allPoint.at(0)->py;
		newE->ex=x;//传入第一点x
		newE->ey=y;//传入第一点y
		newE->nowPointIndex=0;
    	newE->setPosition(Vec2(x,y));
		auto act1= FadeIn::create(1);
		auto act2= CallFunc::create(CC_CALLBACK_0(Enemy::MoveTo,newE));
		newE->getChildByTag(100)->runAction(Sequence::create(act1,act2,NULL));
//		newE->MoveTo();
		return newE;
};	
void Enemy::changeHp(){
	LoadingBar *hpBar= (LoadingBar*)this->getChildByTag(1000);
	hpBar->setPercent(hp/(float)fullHp*100);

}
