#ifndef _SCENEPRODUCT_H_
#define _SCENEPRODUCT_H_

#include "cocos2d.h"
using namespace cocos2d;

class SceneProduct : public Layer {

public:
	SceneProduct();

	virtual ~SceneProduct();

public:

};


class ProductWin :public SceneProduct{

public:
	ProductWin();

	virtual ~ProductWin();

public:
	static Scene* createScene();

	bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(ProductWin);

};

class ProductLose :public SceneProduct{

public:
	ProductLose();

	virtual ~ProductLose();

public:
	static Scene* createScene();

	CREATE_FUNC(ProductLose);

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

};

#endif