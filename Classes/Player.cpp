#include "Player.h"
#include "WinScene.h"
#include "FlowWord.h"
#include "TollgateScene.h"
#include "HelloWorldScene.h"
#include "LoseScene.h"
#include "Collidables.h"

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

void Player::context(ValueMap num1, Point tiledPos) {
	int result = 0;
	if ((num1.find("Collidable") != num1.end()) && (num1.at("Collidable").asString().compare("true") == 0 && isJumping == false))
		doOperationCollidable();
	if (num1.find("food") != num1.end() && num1.at("food").asString().compare("true") == 0)
		doOperationfood(tiledPos);
	if (num1.find("win") != num1.end() && num1.at("win").asString().compare("true") == 0)
		doOperationwin();
}

void Player::doOperationCollidable(){
	isJumping = true;

	auto jumpBy = JumpBy::create(0.8f, Point(-100, 0), 80, 1);
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

void Player::doOperationfood(Point tiledPos){
	/* ���ϰ���������ǰ���ӵ����� */
	TMXLayer* barrier = m_map->getLayer("barrier");
	barrier->removeTileAt(tiledPos);
	Score += 1;
}
void Player::doOperationwin(){
	/* ȡ�ø��ӵ�win����ֵ���ж��Ƿ�Ϊtrue������ǣ�����Ϸʤ������ת��ʤ������ */
	Director::getInstance()->replaceScene(WinScene::createScene());
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
		context(propertiesMap, tiledPos);
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
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();
	Size mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);
	/*���������Ϸ��ʼ�������룬����˵�0���״̬*/
	if (t < 0)
		t = 0;

	/*�������һ�λ��ᣬ�����*/
	if (chance != 0)
	{
		Score = data[t]->getScore();
		//Entity::setTagPosition(data[t]->getPointx(), data[t]->getPointy());
		switch (Score % 6)
		{
		case 1:
			if (data[frameCount - 1]->getPointx() * 2 <= mapSize.width){
				Entity::setTagPosition(data[frameCount - 1]->getPointx() * 2, data[frameCount - 1]->getPointy());
			}
			else {
				Entity::setTagPosition(mapSize.width - 3 * tiledSize.width, data[frameCount - 1]->getPointy());
			}
			break;
		case 2:
			Entity::setTagPosition(data[frameCount - 1]->getPointx() / 2, data[frameCount - 1]->getPointy());
			break;
		case 4:
			Entity::setTagPosition(mapSize.width - 3 * tiledSize.width, data[frameCount - 1]->getPointy());
			break;
		case 5:
			Entity::setTagPosition(0, data[frameCount - 1]->getPointy());
			break;
		default:
			break;
		}
		randomEvent();
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

class Strategy : public Entity {
public:
	Player *player;
	virtual void doOperation(int Score, Size mapSize, Size tiledSize, Sprite* m_sprite, FlowWord* flowWord) {
	}
};
class Operation0 : public Strategy, public Player{
	void doOperation(int Score, Size mapSize, Size tiledSize, Sprite* m_sprite, FlowWord* flowWord) {
		Collidables* collidables = new CollidableOne();
		Score = collidables->change(Score);
		string t = collidables->getInfo().c_str();
		const char* tmp = t.c_str();
		flowWord->showWord(tmp, m_sprite->getPosition());
	}
};
class Operation1 : public Strategy{
	void doOperation(int Score, Size mapSize, Size tiledSize, Sprite* m_sprite, FlowWord* flowWord) {
		Collidables* collidables = new CollidableTwo();
		string t = collidables->getInfo().c_str();
		const char* tmp = t.c_str();
		flowWord->showWord(tmp, m_sprite->getPosition());
	}
};
class Operation2 : public Strategy{
	void doOperation(int Score, Size mapSize, Size tiledSize, Sprite* m_sprite, FlowWord* flowWord) {
		Collidables* collidables = new CollidableThree();
		string t = collidables->getInfo().c_str();
		const char* tmp = t.c_str();
		flowWord->showWord(tmp, m_sprite->getPosition());
	}
};
class Operation3 : public Strategy{
	void doOperation(int Score, Size mapSize, Size tiledSize, Sprite* m_sprite, FlowWord* flowWord) {
		Collidables* collidables = new CollidableOne();
		collidables = new Collidable1(collidables);
		Score = collidables->change(Score);
		string t = collidables->getInfo().c_str();
		const char* tmp = t.c_str();
		flowWord->showWord(tmp, m_sprite->getPosition());
	}
};
class Operation4 : public Strategy{
	void doOperation(int Score, Size mapSize, Size tiledSize, Sprite* m_sprite, FlowWord* flowWord) {
		Collidables* collidables = new CollidableTwo();
		collidables = new Collidable2(collidables);
		string t = collidables->getInfo().c_str();
		const char* tmp = t.c_str();
		flowWord->showWord(tmp, m_sprite->getPosition());
	}
};
class Operation5 : public Strategy{
	void doOperation(int Score, Size mapSize, Size tiledSize, Sprite* m_sprite, FlowWord* flowWord) {
		Collidables* collidables = new CollidableThree();
		collidables = new Collidable3(collidables);
		string t = collidables->getInfo().c_str();
		const char* tmp = t.c_str();
		flowWord->showWord(tmp, m_sprite->getPosition());
	}
};

class Context : public Strategy
{
public:
	Context(int Score, Size mapSize, Size tiledSize, Sprite* m_sprite, FlowWord* flowWord){

		Operation0 *op0 = new Operation0();
		Operation1 *op1 = new Operation1();
		Operation2 *op2 = new Operation2();
		Operation3 *op3 = new Operation3();
		Operation4 *op4 = new Operation4();
		Operation5 *op5 = new Operation5();

		switch (Score % 6)
		{
		case 0:
			this->strategy = op0;
			this->strategy->doOperation(Score, mapSize, tiledSize, m_sprite, flowWord);
			break;
		case 1:
			this->strategy = op1;
			this->strategy->doOperation(Score, mapSize, tiledSize, m_sprite, flowWord);
			break;
		case 2:
			this->strategy = op2;
			this->strategy->doOperation(Score, mapSize, tiledSize, m_sprite, flowWord);
			break;
		case 3:
			this->strategy = op3;
			this->strategy->doOperation(Score, mapSize, tiledSize, m_sprite, flowWord);
			break;
		case 4:
			this->strategy = op4;
			this->strategy->doOperation(Score, mapSize, tiledSize, m_sprite, flowWord);
			break;
		case 5:
			this->strategy = op5;
			this->strategy->doOperation(Score, mapSize, tiledSize, m_sprite, flowWord);
			break;
		}
	}

	Strategy *strategy;
};

void Player::randomEvent()
{
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();
	Size mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);
	FlowWord* flowWord = FlowWord::create();
	this->addChild(flowWord);
	/*���ݵ�ǰ������6��ģ��ȡ��Ӧ��ײ�¼�*/

	Context context(Score, mapSize, tiledSize, m_sprite, flowWord);

}
