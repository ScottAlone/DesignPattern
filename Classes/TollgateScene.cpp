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

	/* ����Tiled��ͼ����ӵ������� */
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

	/* �������� */
	Sprite* playerSprite = Sprite::create("tank1.png");

	/* ������󶨵���Ҷ����� */
	Player* mPlayer = Player::create();
	mPlayer->bindSprite(playerSprite);
	mPlayer->run();
	mPlayer->setTiledMap(map);

	/* ���ض���� */
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	/* �������������� */
	ValueMap playerPointMap = objGroup->getObject("PlayerPoint");
	float playerX = playerPointMap.at("x").asFloat();
	float playerY = playerPointMap.at("y").asFloat();

	/* ����������� */
	mPlayer->setPosition(Point(playerX,playerY));

	/* �������ӵ���ͼ */
	map->addChild(mPlayer);

	/* ------------ ��������ƶ������� -------------- */
	ThreeDirectionController* threeMoveControll = ThreeDirectionController::create();
	threeMoveControll->setiXSpeed(4);
	threeMoveControll->setiYSpeed(0);

	/* ������Ҫ��ӵ������в��ܻ��update�¼� */
	this->addChild(threeMoveControll);

	/* ���ÿ��������������� */
	mPlayer->setController(threeMoveControll);
}

void TollgateScene::update(float)
{
	static_cast<Label*>(this->getChildByName("label"))->setString(StringUtils::format("score:%d", Player::getScore()));
}