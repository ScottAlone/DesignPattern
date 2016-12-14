#ifndef _SCENEPRODUCT_H_
#define _SCENEPRODUCT_H_

#include "cocos2d.h"
#include <string>
using namespace cocos2d;
using  std::string;
USING_NS_CC;

class SceneProduct : public Layer {
public:
	virtual bool init() = 0;
};


class ProductWin :public SceneProduct{
public:
	static Scene* createScene();

	static ProductWin* create();

	bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

};

class ProductLose :public SceneProduct{
public:
	static Scene* createScene();

	static ProductLose* create();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

};

class ProductHelp :public SceneProduct{
public:
	static Scene* createScene();

	static ProductHelp* create();

	virtual bool init();

	virtual void createLabel(string content, string font, int size, int width, int height);

	void menuCloseCallback(cocos2d::Ref* pSender);

};

class ProductGate :public SceneProduct{
public:
	static Scene* createScene();

	static ProductGate* create();

	virtual bool init();

	void addPlayer(TMXTiledMap* map);

	virtual void update(float);

};

class ProductStart :public SceneProduct{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	void menuCloseCallback1(cocos2d::Ref* pSender);

	static ProductStart* create();

private:
	cocos2d::Animate* createAnimate1();

};

#endif