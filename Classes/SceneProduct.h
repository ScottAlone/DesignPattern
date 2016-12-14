#ifndef _SCENEPRODUCT_H_
#define _SCENEPRODUCT_H_

#include "cocos2d.h"
#include "SceneProduct.h"
#include <string>
using namespace cocos2d;
using  std::string;
using namespace std;
USING_NS_CC;

class SceneProduct : public Layer {

public:
	SceneProduct();

	virtual ~SceneProduct();

public:

	static Scene* createScene(int flag) {
		if (flag == 1) {
			auto scene = Scene::create();
			auto layer = ProductHelp::create();
			scene->addChild(layer);
			return scene;
		}
		if (flag == 2) {
			auto scene = Scene::create();
			auto layer = ProductWin::create();
			scene->addChild(layer);
			return scene;
		}
		if (flag == 3) {
			auto scene = Scene::create();
			auto layer = ProductLose::create();
			scene->addChild(layer);
			return scene;
		}
		if (flag == 4) {
			auto scene = Scene::create();
			auto layer = ProductGate::create();
			scene->addChild(layer);
			return scene;
		}

	}

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

class ProductHelp {

public:
	ProductHelp();

	virtual ~ProductHelp();

public:
	static Scene* createScene();

	CREATE_FUNC(ProductHelp);

	virtual bool init();

	virtual void createLabel(string content, string font, int size, int width, int height);

	void menuCloseCallback(cocos2d::Ref* pSender);

};

class ProductGate :public SceneProduct{

public:
	ProductGate();

	virtual ~ProductGate();

public:
	static Scene* createScene();

	CREATE_FUNC(ProductGate);

	virtual bool init();

	void addPlayer(TMXTiledMap* map);

	virtual void update(float);

};

class ProductStart :public SceneProduct{

public:
	ProductStart();

	virtual ~ProductStart();

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	void menuCloseCallback1(cocos2d::Ref* pSender);

	CREATE_FUNC(ProductStart);

private:
	cocos2d::Animate* createAnimate1();

};

#endif