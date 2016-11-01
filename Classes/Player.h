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
private:
	TMXTiledMap* m_map;
	bool isJumping;
	static int Score;
	TMXLayer* meta;
	Point tileCoordForPosition(Point pos);
	cocos2d::Animate* createAnimate1();
};
#endif