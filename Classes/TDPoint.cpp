#include "TDPoint.h"
TDPoint* TDPoint::createPoint(int x,int y){
	TDPoint * td = new TDPoint();
	td->autorelease();
	td->px=x;
	td->py=y;
	return td; 
	               
}