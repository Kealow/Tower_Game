#include "Boom.h"
bool Boom::init(){
	if(!Node::init()){
		return false;
	}

	return true;
}
Boom* Boom::createBoom(int x, int y){
	Boom *newb = Boom::create();
	auto ps = ParticleSystemQuad::create("boom.plist");
	ps->setPosition(x,y);
	newb->addChild(ps);
	newb->setPosition(Point::ZERO);
	newb->runAction(Sequence::create(DelayTime::create(0.5),
		CCCallFuncN::create(newb,callfuncN_selector(Boom::killSelf)),
		NULL
		));
		
	return newb;
}
void Boom::killSelf(Node *obj){
	obj->removeFromParent();
}