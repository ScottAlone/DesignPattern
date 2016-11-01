#ifndef _LoseScene_H_
#define _LoseScene_H_

#include "cocos2d.h"

using namespace cocos2d;

class LoseScene : public Layer {
public:
	static Scene* createScene();
	CREATE_FUNC(LoseScene);
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

};

#endif