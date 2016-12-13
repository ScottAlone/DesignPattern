#ifndef _WinScene_H_
#define _WinScene_H_

#include "cocos2d.h"

using namespace cocos2d;

class WinScene : public Layer {
public:
	static Scene* createScene();
	CREATE_FUNC(WinScene);
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif
