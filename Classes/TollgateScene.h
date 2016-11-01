#ifndef _TollgateScene_H_
#define _TollgateScene_H_

#include "cocos2d.h"
using namespace cocos2d;

class TollgateScene : public Layer {
public:
	static Scene* createScene();
	CREATE_FUNC(TollgateScene);
	virtual bool init();
	void addPlayer(TMXTiledMap* map);
	virtual void update(float);

};
#endif