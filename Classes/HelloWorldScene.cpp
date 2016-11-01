#include "HelloWorldScene.h"
#include "Tollgatescene.h"
#include "HelpScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
		"bgm.mp3", true);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "StartGame1.png",
                                           "StartGame2.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(visibleSize.width / 2 + origin.x - 325, visibleSize.height / 2 + origin.y + 115));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	auto closeItem1 = MenuItemImage::create(
		"Introduction.png",
		"Introduction2.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback1, this));

	closeItem1->setPosition(Vec2(visibleSize.width / 2 + origin.x - 325, visibleSize.height / 2 + origin.y + 15));

	// create menu, it's an autorelease object
	auto menu1 = Menu::create(closeItem1, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    /*auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);*/

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("StartScene.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
/*#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif*/
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TollgateScene::createScene()));
}

void HelloWorld::menuCloseCallback1(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, HelpScene::createScene()));
}
cocos2d::Animate* HelloWorld::createAnimate1()
{
	int iFrameNum = 3;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	/* 用一个列表保存所有SpriteFrame对象 */
	for (int i = 1; i <= iFrameNum; i++) {
		/* 用每一张图片创建SpriteFrame对象 */
		frame = SpriteFrame::create(StringUtils::format("tank%d.png", i), Rect(0, 0, 130, 130));
		frameVec.pushBack(frame);
	}

	/* 使用SpriteFrame列表创建动画对象 */
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	/* 将动画包装成一个动作 */
	Animate* action = Animate::create(animation);

	return action;
}

cocos2d::Animate* HelloWorld::createAnimate2()
{
	/* 加载图片帧到缓存池 */
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("boys.plist", "boys.png");

	int iFrameNum = 15;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	/* 用一个列表保存所有SpriteFrame对象 */
	for (int i = 1; i <= iFrameNum; i++) {
		/* 从SpriteFrame缓存池中获取SpriteFrame对象 */
		frame = frameCache->getSpriteFrameByName(StringUtils::format("run%d.png", i));
		frameVec.pushBack(frame);
	}

	/* 使用SpriteFrame列表创建动画对象 */
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);

	/* 将动画包装成一个动作 */
	Animate* action = Animate::create(animation);

	return action;
}

