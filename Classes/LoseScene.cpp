#include "LoseScene.h"
#include "TollgateScene.h"

USING_NS_CC;

Scene* LoseScene::createScene() {
	auto scene = Scene::create();
	auto layer = LoseScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoseScene::init() {
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
		CC_CALLBACK_1(LoseScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(visibleSize.width / 2 + origin.x - 410, visibleSize.height / 2 + origin.y - 235));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void LoseScene::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TollgateScene::createScene()));
}
