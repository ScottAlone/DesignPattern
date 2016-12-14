#include "SceneProduct.h"
#include "Player.h"
#include"ThreeDirectionController.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"
#include <string>

using  std::string;
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

ProductHelp::ProductHelp(){
}

ProductHelp::~ProductHelp(){
}

ProductGate::ProductGate(){
}

ProductGate::~ProductGate(){
}

ProductStart::ProductStart(){
}

ProductStart::~ProductStart(){
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
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ProductGate::createScene()));
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
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ProductGate::createScene()));
}

void ProductHelp::createLabel(string content, string font, int size, int width, int height) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Label* Lab = Label::createWithSystemFont(content, font, size);
	Lab->setPosition(Point(width, height));
	this->addChild(Lab);
}

bool ProductHelp::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto closeItem = MenuItemImage::create(
		"StartGame1.png",
		"StartGame2.png",
		CC_CALLBACK_1(ProductHelp::menuCloseCallback, this));

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
	sprite2->setPosition(Vec2(visibleSize.width / 2 + origin.x - 150, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite2, 0);

	return true;
}

void ProductHelp::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ProductGate::createScene()));
}

bool ProductGate::init() {
	if (!Layer::init()) {
		return false;
	}

	/* 加载Tiled地图，添加到场景中 */
	TMXTiledMap* map = TMXTiledMap::create("level05.tmx");
	TMXLayer* groundLayer = map->layerNamed("ground");

	this->addChild(map);
	addPlayer(map);
	auto label = Label::createWithSystemFont("score:  hp:", "", 30);
	this->addChild(label, 10, "label");
	label->setPosition(Vec2(120, 665));
	label->setString(StringUtils::format("score:%d hp:%d", Player::getScore(), Player::getHp()));
	this->scheduleUpdate();
	return true;
}

void ProductGate::addPlayer(TMXTiledMap* map) {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/* 创建精灵 */
	Sprite* playerSprite = Sprite::create("tank1.png");

	/* 将精灵绑定到玩家对象上 */
	Player* mPlayer = Player::create();
	mPlayer->bindSprite(playerSprite);
	mPlayer->run();
	mPlayer->setTiledMap(map);

	/* 加载对象层 */
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	/* 加载玩家坐标对象 */
	ValueMap playerPointMap = objGroup->getObject("PlayerPoint");
	float playerX = playerPointMap.at("x").asFloat();
	float playerY = playerPointMap.at("y").asFloat();

	/* 设置玩家坐标 */
	mPlayer->setPosition(Point(playerX, playerY));

	/* 将玩家添加到地图 */
	map->addChild(mPlayer);

	/* ------------ 创建玩家移动控制器 -------------- */
	ThreeDirectionController* threeMoveControll = ThreeDirectionController::create();
	threeMoveControll->setiXSpeed(4);
	threeMoveControll->setiYSpeed(0);

	/* 控制器要添加到场景中才能获得update事件 */
	this->addChild(threeMoveControll);

	/* 设置控制器到主角身上 */
	mPlayer->setController(threeMoveControll);
}

void ProductGate::update(float) {
	static_cast<Label*>(this->getChildByName("label"))->setString(StringUtils::format("score:%d hp:%d", Player::getScore(), Player::getHp()));
}

SceneManager *scene;
Scene* ProductStart::createScene() {
	auto scene = Scene::create();

	auto layer = ProductStart::create();

	scene->addChild(layer);

	return scene;
}

bool ProductStart::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
		"bgm.mp3", true);

	auto closeItem = MenuItemImage::create(
		"StartGame1.png",
		"StartGame2.png",
		CC_CALLBACK_1(ProductStart::menuCloseCallback, this));

	closeItem->setPosition(Vec2(visibleSize.width / 2 + origin.x - 325, visibleSize.height / 2 + origin.y + 115));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto closeItem1 = MenuItemImage::create(
		"Introduction.png",
		"Introduction2.png",
		CC_CALLBACK_1(ProductStart::menuCloseCallback1, this));

	closeItem1->setPosition(Vec2(visibleSize.width / 2 + origin.x - 325, visibleSize.height / 2 + origin.y + 15));

	auto menu1 = Menu::create(closeItem1, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);
	auto sprite = Sprite::create("StartScene.png");

	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(sprite, 0);

	return true;
}

void ProductStart::menuCloseCallback(Ref* pSender) {
	scene->tollgateScene();
}

void ProductStart::menuCloseCallback1(Ref* pSender) {
	scene->helpScene();
}
cocos2d::Animate* ProductStart::createAnimate1() {
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