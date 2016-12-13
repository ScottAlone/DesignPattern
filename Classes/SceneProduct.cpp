#include "SceneProduct.h"
#include "TollgateScene.h"

USING_NS_CC;

SceneProduct::SceneProduct(){
}


SceneProduct::~SceneProduct(){
}


ProductWin::ProductWin(){
}


ProductWin::~ProductWin(){
}

ProductLose::ProductLose(){
}


ProductLose::~ProductLose(){
}


Scene* ProductWin::createScene() {
	auto scene = Scene::create();
	auto layer = ProductWin::create();
	scene->addChild(layer);

	return scene;
}

bool ProductWin::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("Win.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	auto closeItem = MenuItemImage::create(
		"TryAgain.png",
		"TryAgain1.png",
		CC_CALLBACK_1(ProductWin::menuCloseCallback, this));

	closeItem->setPosition(Vec2(visibleSize.width / 2 + origin.x - 410, visibleSize.height / 2 + origin.y - 235));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void ProductWin::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TollgateScene::createScene()));
}


Scene* ProductLose::createScene() {
	auto scene = Scene::create();
	auto layer = ProductLose::create();
	scene->addChild(layer);
	return scene;
}

bool ProductLose::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("Lose.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	auto closeItem = MenuItemImage::create(
		"TryAgain.png",
		"TryAgain1.png",
		CC_CALLBACK_1(ProductLose::menuCloseCallback, this));

	closeItem->setPosition(Vec2(visibleSize.width / 2 + origin.x - 410, visibleSize.height / 2 + origin.y - 235));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void ProductLose::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TollgateScene::createScene()));
}
