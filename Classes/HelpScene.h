#ifndef _HelpScene_H_
#define _HelpScene_H_

#include "cocos2d.h"

using namespace cocos2d;

class HelpScene : public Layer {
public:
	static Scene* createScene();
	CREATE_FUNC(HelpScene);
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif