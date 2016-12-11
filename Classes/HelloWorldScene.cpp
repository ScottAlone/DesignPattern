#include "HelloWorldScene.h"
#include "Tollgatescene.h"
#include "HelpScene.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"

USING_NS_CC;

SceneManager *scene;
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
		"bgm.mp3", true);

    auto closeItem = MenuItemImage::create(
                                           "StartGame1.png",
                                           "StartGame2.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(visibleSize.width / 2 + origin.x - 325, visibleSize.height / 2 + origin.y + 115));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	auto closeItem1 = MenuItemImage::create(
		"Introduction.png",
		"Introduction2.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback1, this));

	closeItem1->setPosition(Vec2(visibleSize.width / 2 + origin.x - 325, visibleSize.height / 2 + origin.y + 15));

	auto menu1 = Menu::create(closeItem1, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);

    auto sprite = Sprite::create("StartScene.png");

    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(sprite, 0);
    
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	scene->tollgateScene();
}

void HelloWorld::menuCloseCallback1(Ref* pSender)
{
	scene->helpScene();
}
cocos2d::Animate* HelloWorld::createAnimate1()
{
	int iFrameNum = 3;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 1; i <= iFrameNum; i++) {
		frame = SpriteFrame::create(StringUtils::format("tank%d.png", i), Rect(0, 0, 130, 130));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	Animate* action = Animate::create(animation);

	return action;
}

