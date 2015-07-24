#ifndef _GameLayer_
#define _GameLayer_
#include "cocos2d.h"
#include "TDPoint.h"
#include "Enemy.h"
#include "TD.h"
#include "Bullet.h"
#include "Mode.h"
USING_NS_CC;
class GameLayer:public Layer,public GameDelegate
{
public:
	int fullHp;
	int hp;
	int nowLevel;
	int npcGroupCount;
	int npcNumberCount;
	int npcGroupIndex;//当前第几波
	int npcNumberIndex;//当前第几只
	ValueVector levelAllNpc ;//当前关卡所有怪物定义


	int money;
	int mapdetail[15][10];
	int nowrow,nowcol;
	int enemyCount;
    static Vector<TDPoint*> allPoint;
	static Vector<Bullet *> allBullet;
	static Vector<Enemy *>  allEnemy;
	static Vector<TD *> allTD;
	CREATE_FUNC(GameLayer);
	static Scene * createScene();
	bool init();
	void initAllPoint(TMXTiledMap *m);//加载地图对象层每个点
	void newEnemy(float t);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
	void addTDSelect(int r,int c);
	void addTowerUp(int r,int c);
	void sellTD(Ref *obj);
	void upTower(Ref *obj);
	void selectTD(Ref *obj);
	void update(float t);
	void initLevel();//初始化当前关卡
	void changePlayerHp();
	void setLevel();
	void selectLevel(int l);
	static GameLayer* getInstance();

};
#endif
