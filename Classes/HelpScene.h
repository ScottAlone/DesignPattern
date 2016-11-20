#ifndef _HelpScene_H_
#define _HelpScene_H_
#include <string>
#include "cocos2d.h"

using  std::string;
using namespace cocos2d;

class HelpScene : public Layer {
public:
	static Scene* createScene();
	CREATE_FUNC(HelpScene);
	virtual bool init();
	virtual void createLabel(string content, string font, int size, int width, int height);
	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif