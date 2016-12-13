#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "HelpScene.h"
#include "SceneFactory.h"
#include "SceneProduct.h"
#include "TollgateScene.h"
#include "cocos2d.h"
USING_NS_CC;

class SceneManager {
public:
	void helpScene() { 
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, HelpScene::createScene())); 
	}
	void winScene() { 
		FactoryWin* fw = new FactoryWin();
		ProductWin* product = fw->createProduct();
		Director::getInstance()->replaceScene(product->createScene()); 
	}
	void loseScene() {
		FactoryLose* fl = new FactoryLose();
		ProductLose* product = fl->createProduct();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, product->createScene()));
	}
	void tollgateScene() {
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TollgateScene::createScene())); 
	}
};
#endif
