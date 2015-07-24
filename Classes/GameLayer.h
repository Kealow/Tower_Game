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
	int npcGroupIndex;//��ǰ�ڼ���
	int npcNumberIndex;//��ǰ�ڼ�ֻ
	ValueVector levelAllNpc ;//��ǰ�ؿ����й��ﶨ��


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
	void initAllPoint(TMXTiledMap *m);//���ص�ͼ�����ÿ����
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
	void initLevel();//��ʼ����ǰ�ؿ�
	void changePlayerHp();
	void setLevel();
	void selectLevel(int l);
	static GameLayer* getInstance();

};
#endif
