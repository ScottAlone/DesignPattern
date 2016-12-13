#include "HelpScene.h"
#include "TollgateScene.h"
#include <string>

using  std::string;
USING_NS_CC;

Scene* HelpScene::createScene() {
	auto scene = Scene::create();
	auto layer = HelpScene::create();
	scene->addChild(layer);

	return scene;
}

void HelpScene::createLabel(string content, string font, int size, int width, int height){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Label* Lab = Label::createWithSystemFont(content, font, size);
	Lab->setPosition(Point(width, height));
	this->addChild(Lab);
}

bool HelpScene::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto closeItem = MenuItemImage::create(
		"StartGame1.png",
		"StartGame2.png",
		CC_CALLBACK_1(HelpScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	createLabel("Introduction", "Arial", 60, visibleSize.width / 2, visibleSize.height / 2 + 275);
	createLabel("The tank is running on the road!", "Arial", 45, visibleSize.width / 2, visibleSize.height / 2 + 200);
	createLabel("Try to avoid            !", "Arial", 45, visibleSize.width / 2, visibleSize.height / 2 + 100);
	createLabel("Pick up             to increase your score!", "Arial", 45, visibleSize.width / 2, visibleSize.height / 2);
	createLabel("Use your mouse to move.", "Arial", 45, visibleSize.width / 2, visibleSize.height / 2 - 100);
	createLabel("Good luck!", "Arial", 45, visibleSize.width / 2, visibleSize.height / 2 - 200);

	auto sprite1 = Sprite::create("Collidable.png");

	// position the sprite on the center of the screen
	sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x + 110, visibleSize.height / 2 + origin.y + 100));

	// add the sprite as a child to this layer
	this->addChild(sprite1, 0);

	auto sprite2 = Sprite::create("food.jpg");

	// position the sprite on the center of the screen
	sprite2->setPosition(Vec2(visibleSize.width / 2 + origin.x - 150 , visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite2, 0);

	return true;
}

void HelpScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f,TollgateScene::createScene()));
}
