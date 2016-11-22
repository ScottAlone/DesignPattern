#ifndef _Player_H_
#define _Player_H_

#include "Entity.h"

class Player : public Entity
{
public:
	CREATE_FUNC(Player);
	virtual bool init();
	virtual void setTagPosition(int x, int y) override;

	void run();
	void setViewPointByPlayer();
	static int getScore(){ return Score; }
	void resetData();
	void setTiledMap(TMXTiledMap* map);
	void rollBack();
	void isOver();
private:
	TMXTiledMap* m_map;
	bool isJumping;
	static int Score;
	TMXLayer* meta;
	Point tileCoordForPosition(Point pos);
	cocos2d::Animate* createAnimate1();
};
class rollBackData
{
public:
	rollBackData(Point p, int s){ point = p; score = s; };
	int getPointx(){ return point.x; };
	int getPointy(){ return point.y; };
	int getScore(){ return score; };
private:
	Point point;
	int score;
};
#endif