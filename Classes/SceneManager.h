#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "SceneFactory.h"
#include "SceneProduct.h"
#include "cocos2d.h"
USING_NS_CC;

class SceneManager {
public:
	void helpScene();

	void winScene();

	void loseScene();

	void tollgateScene();

};
#endif
