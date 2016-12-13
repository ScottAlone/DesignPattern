#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "HelpScene.h"
#include "LoseScene.h"
#include "WinScene.h"
#include "TollgateScene.h"
#include "cocos2d.h"
USING_NS_CC;

class SceneManager {
public:
	void helpScene() { 
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, HelpScene::createScene())); 
	}
	void winScene() { 
		Director::getInstance()->replaceScene(WinScene::createScene()); 
	}
	void loseScene() {
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LoseScene::createScene())); 
	}
	void tollgateScene() {
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TollgateScene::createScene())); 
	}
};
#endif
