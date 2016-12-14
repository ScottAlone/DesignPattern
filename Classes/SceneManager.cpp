#include "SceneFactory.h"
#include "SceneProduct.h"
#include "SceneManager.h"
#include "cocos2d.h"
USING_NS_CC;

void SceneManager::helpScene() {
	SceneFactory* fh = new FactoryHelp();
	SceneProduct* product = fh->createProduct();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, product->createScene(1)));
}
void SceneManager::winScene() {
	SceneFactory* fh = new FactoryWin();
	SceneProduct* product = fh->createProduct();
	Director::getInstance()->replaceScene(product->createScene(2));
}
void SceneManager::loseScene() {
	SceneFactory* fh = new FactoryLose();
	SceneProduct* product = fh->createProduct();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, product->createScene(3)));
}
void SceneManager::tollgateScene() {
	SceneFactory* fh = new FactoryGate();
	SceneProduct* product = fh->createProduct();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, product->createScene(4)));
}