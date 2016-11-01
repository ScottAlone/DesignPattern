#include "HelpScene.h"
#include "TollgateScene.h"

USING_NS_CC;

Scene* HelpScene::createScene() {
	auto scene = Scene::create();
	auto layer = HelpScene::create();
	scene->addChild(layer);

	return scene;
}

bool HelpScene::init() {
	if (!Layer::init())
	{
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


	Label* Lab = Label::createWithSystemFont("Introduction", "Arial", 60);
	Lab->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2+275));
	this->addChild(Lab);

	Label* Lab1 = Label::createWithSystemFont("The tank is running on the road!", "Arial", 45);
	Lab1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2+200));
	this->addChild(Lab1);
	
	Label* Lab2 = Label::createWithSystemFont("Try to avoid            !", "Arial", 45);
	Lab2->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2+100));
	this->addChild(Lab2);

	Label* Lab3 = Label::createWithSystemFont("Pick up             to increase your score!", "Arial", 45);
	Lab3->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(Lab3);

	Label* Lab4 = Label::createWithSystemFont("Use your mouse to move.", "Arial", 45);
	Lab4->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2-100));
	this->addChild(Lab4);

	Label* Lab5 = Label::createWithSystemFont("Good luck!", "Arial", 45);
	Lab5->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2-200));
	this->addChild(Lab5);

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
/*#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif*/
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f,TollgateScene::createScene()));
}
