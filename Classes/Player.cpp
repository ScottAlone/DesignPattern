#include "Player.h"
#include "WinScene.h"
#include "FlowWord.h"
#include "TollgateScene.h"
#include "HelloWorldScene.h"
#include "LoseScene.h"

rollBackData *data[10000];
int frameCount = 0;
int chance = 1;
int Player::Score = 0;
bool Player::init() {
	isJumping = false;
	return true;
}

void Player::run() {
	int iFrameNum = 3;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 1; i <= iFrameNum; i++) {
		/* ��ÿһ��ͼƬ����SpriteFrame���� */
		frame = SpriteFrame::create(StringUtils::format("tank%d.png", i), Rect(0, 0, 130, 130));
		frameVec.pushBack(frame);
	}
	;
	//* ���ݾ���֡���󴴽��������� */
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);    // ѭ������
	animation->setDelayPerUnit(0.04f);  // ÿ֡���ż��

	/* ������������ */
	Animate* animate = Animate::create(animation);


	/* ����ִ�ж��� */
	m_sprite->runAction(animate);

}

void Player::setViewPointByPlayer() {
	if (m_sprite == NULL) {
		return;
	}
	Layer* parent = (Layer*)getParent();

	/* ��ͼ�������� */
	Size mapTiledNum = m_map->getMapSize();

	/* ��ͼ�������Ӵ�С */
	Size tiledSize = m_map->getTileSize();

	/*��ͼ��С */
	Size mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);

	/* ��Ļ��С */
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/* �������� */
	Point spritePos = getPosition();

	/* �����������С����Ļ��һ�룬��ȡ��Ļ�е����꣬����ȡ���ǵ����� */
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	/* ���X��Y������������Ͻǵļ���ֵ����ȡ����ֵ�����꣨����ֵ��ָ���õ�ͼ����
	��Ļ��ɳ��ֺڱߵļ������꣩ */
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	/* Ŀ��� */
	Point destPos = Point(x, y);

	/* ��Ļ�е� */
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	/* ������Ļ�е����Ҫ�ƶ���Ŀ�ĵ�֮��ľ��� */
	Point viewPos = centerPos - destPos;

	parent->setPosition(viewPos);
}

void Player::setTagPosition(int x, int y) {
	/* -----------------�ж�ǰ���Ƿ񲻿�ͨ��---------------- */
	/* ȡ����ǰ�������� */
	Size spriteSize = m_sprite->getContentSize();
	Point dstPos = Point(x + spriteSize.width / 2, y);

	/*��ÿ֡��ʵ����һ���ع���������ڴ洢״̬*/
	data[frameCount] = new rollBackData(Point(x, y), Score);
	frameCount++;

	/* ��õ�ǰ����ǰ�������ڵ�ͼ�еĸ���λ�� */
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));

	/* ��ȡ��ͼ���ӵ�Ψһ��ʶ */
	int tiledGid = meta->getTileGIDAt(tiledPos);

	/* ��Ϊ0���������������� */
	if (tiledGid != 0) {
		/*
		��ȡ�õ�ͼ���ӵ��������ԣ�Ŀǰ����ֻ��һ��Collidable����
		����������meta��ģ���ͬʱҲ������������ͼ�ģ������ڻ�ȡ���ӵ���������
		ʱ��ͨ������Ψһ��ʶ�ڵ�ͼ��ȡ��
		*/
		Value properties = m_map->getPropertiesForGID(tiledGid);

		ValueMap propertiesMap = properties.asValueMap();

		if (propertiesMap.find("Collidable") != propertiesMap.end())
		{
			/* ȡ�ø��ӵ�Collidable����ֵ */
			Value prop = propertiesMap.at("Collidable");
			/* �ж�Collidable�����Ƿ�Ϊtrue������ǣ���������ƶ� */
			if (prop.asString().compare("true") == 0 && isJumping == false) {
				isJumping = true;

				auto jumpBy = JumpBy::create(0.5f, Point(-100, 0), 80, 1);
				CallFunc* callfunc = CallFunc::create([&](){
					/* �ָ�״̬ */
					rollBack();
				});

				/* ִ�ж�������ײ���ϰ���ʱ�ķ���Ч�� */
				auto actions = Sequence::create(jumpBy, callfunc, NULL);
				this->runAction(actions);
				FlowWord* flowWord = FlowWord::create();
				this->addChild(flowWord);
				flowWord->showWord("oh no!", m_sprite->getPosition());
				//Score = 0;

				//stopAllActions();	/* ��ֹͣ��������ִ�еĶ��� */
				//resetData();		/* �������� */
				//TMXLayer* barrier = m_map->getLayer("barrier");
				//barrier->removeTileAt(tiledPos);
				//removeChild(this, true);
				isOver();
			}
		}
		if (propertiesMap.find("food") != propertiesMap.end())
		{
			/* ȡ�ø��ӵ�food����ֵ���ж��Ƿ�Ϊtrue������ǣ����ø����ϵ�������ʧ */
			Value prop = properties.asValueMap().at("food");
			if (prop.asString().compare("true") == 0) {
				/* ���ϰ���������ǰ���ӵ����� */
				TMXLayer* barrier = m_map->getLayer("barrier");
				barrier->removeTileAt(tiledPos);
				Score += 1;
			}
		}

		if (propertiesMap.find("win") != propertiesMap.end())
		{
			/* ȡ�ø��ӵ�food����ֵ���ж��Ƿ�Ϊtrue������ǣ����ø����ϵ�������ʧ */
			Value prop = properties.asValueMap().at("win");
			if (prop.asString().compare("true") == 0) {
				/* ȡ�ø��ӵ�win����ֵ���ж��Ƿ�Ϊtrue������ǣ�����Ϸʤ������ת��ʤ������ */
				Director::getInstance()->replaceScene(WinScene::createScene());
			}
		}
	}


	Entity::setTagPosition(x, y);

	/* ������Ϊ�����ƶ���ͼ */
	setViewPointByPlayer();
}

void Player::setTiledMap(TMXTiledMap* map)
{
	m_map = map;
	this->meta = m_map->getLayer("meta");
	this->meta->setVisible(false);
}

Point Player::tileCoordForPosition(Point pos) {
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();

	int x = pos.x / tiledSize.width;

	/* Cocos2d-x��Ĭ��Y�������������ϵģ�����Ҫ��һ��������� */
	int y = (700 - pos.y) / tiledSize.height;

	/* ����������㿪ʼ���� */
	if (x > 0) {
		x -= 1;
	}
	if (y > 0) {
		y -= 0;
	}

	return Point(x, y);
}

void Player::rollBack(){
	/*���˵�������ǰ��״̬*/
	int t = frameCount - 60 * 2;

	/*���������Ϸ��ʼ�������룬����˵�0���״̬*/
	if (t < 0)
		t = 0;

	/*�������һ�λ��ᣬ�����*/
	if (chance != 0)
	{
		Score = data[t]->getScore();
		Entity::setTagPosition(data[t]->getPointx(), data[t]->getPointy());
	}
	chance--;
	isJumping = false;
}

void Player::isOver()
{
	if (chance == 0)
	{
		/*����������չʾʧ�ܳ���*/
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LoseScene::createScene()));

		/*�����������*/
		memset(data, 0, sizeof(data));
		frameCount = 0;
		Score = 0;
	}
	else if (chance < 0)
		/*���try again��ָ�������*/
		chance = 1;
}

//int Player::getScore() {
//	return this->Score;
//}

void Player::resetData() {
	if (isJumping) {
		isJumping = false;
	}
}
