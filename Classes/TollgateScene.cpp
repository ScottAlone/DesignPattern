#include "TollgateScene.h"
#include"SimpleMoveController.h"
#include "Player.h"
#include"ThreeDirectionController.h"

Scene* TollgateScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);

	return scene;
}

bool TollgateScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	/* 加载Tiled地图，添加到场景中 */
	TMXTiledMap* map = TMXTiledMap::create("level05.tmx");
	TMXLayer* groundLayer = map->layerNamed("ground");

	this->addChild(map);
	addPlayer(map);
	auto label = Label::createWithSystemFont("score:", "", 30);
	this->addChild(label, 10,"label");
	label->setPosition(Vec2(75, 675));
	label->setString(StringUtils::format("score:%d", Player::getScore()));
	this->scheduleUpdate();
	return true;
}

void TollgateScene::addPlayer(TMXTiledMap* map) {
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
	mPlayer->setPosition(Point(playerX,playerY));

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

void TollgateScene::update(float)
{
	static_cast<Label*>(this->getChildByName("label"))->setString(StringUtils::format("score:%d", Player::getScore()));
}