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
		//��Ѫ
		//��ΪchangeHP���Ǿ�̬���������Բ���ֱ���������á�����ΪEnemy�ĸ��ڵ���GameLayer������Ӧ�ȴ��������ٽ��е��á�
	//	GameLayer * gs = (GameLayer *)this->getParent();
	//	gs->changePlayerHp();
		GameLayer::getInstance()->changePlayerHp();
		//����
		GameLayer::allEnemy.eraseObject(this);
		this->removeFromParent();
		return;
	}
	int x = GameLayer::allPoint.at(nowPointIndex)->px;//��һ���������
	int y = GameLayer::allPoint.at(nowPointIndex)->py;
//	int distance = sqrt((x-this->ex)*(x-this->ex)+(y-this->ey)*(y-this->ey));
	int distance = Vec2(x,y).getDistance(Vec2(ex,ey));
	int time = distance/this->speed;
	this->ex=x;//������ݴ�����ȥ
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
		sp->setOpacity(0);//���þ���͸��
		sp->setTag(100);
		sp->runAction(RepeatForever::create(ani));
		newE->addChild(sp);
		//����Ѫ��
		auto hpbar = LoadingBar::create("return.png");
		hpbar->setTag(1000);
		hpbar->setPercent(100);
		hpbar->setPositionY(32);
		newE->addChild(hpbar,1);
	//�ƶ�����
		int x = GameLayer::allPoint.at(0)->px;
		int y = GameLayer::allPoint.at(0)->py;
		newE->ex=x;//�����һ��x
		newE->ey=y;//�����һ��y
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
