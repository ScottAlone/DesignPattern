#include "SceneFactory.h"
#include "SceneProduct.h"
#include "SceneManager.h"
#include "cocos2d.h"
USING_NS_CC;

void SceneManager::helpScene() {
	FactoryHelp* fh = new FactoryHelp();
	ProductHelp* product = fh->createProduct();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, product->createScene()));
}
void SceneManager::winScene() {
	FactoryWin* fw = new FactoryWin();
	ProductWin* product = fw->createProduct();
	Director::getInstance()->replaceScene(product->createScene());
}
void SceneManager::loseScene() {
	FactoryLose* fl = new FactoryLose();
	ProductLose* product = fl->createProduct();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, product->createScene()));
}
void SceneManager::tollgateScene() {
	FactoryGate* fg = new FactoryGate();
	ProductGate* product = fg->createProduct();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, product->createScene()));
}