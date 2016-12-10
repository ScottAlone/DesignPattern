#include "Player.h"
#include "WinScene.h"
#include "FlowWord.h"
#include "TollgateScene.h"
#include "HelloWorldScene.h"
#include "LoseScene.h"
#include "Collidables.h"
#include "Observer.h"

rollBackData *data[10000];
int frameCount = 0;
int chance = 3;
int Player::Score = 0;
HP *myHp = new MyHp();
Mapsize *p1 = Mapsize::GetInstance();

bool Player::init() {
	Observer *observer1 = new ObserverHp(myHp);
	myHp->Attach(observer1);
	myHp->InitStatus(100);
	myHp->Notify();
	isJumping = false;
	return true;
}

void Player::run() {
	int iFrameNum = 3;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 1; i <= iFrameNum; i++) {
		/* 用每一张图片创建SpriteFrame对象 */
		frame = SpriteFrame::create(StringUtils::format("tank%d.png", i), Rect(0, 0, 130, 130));
		frameVec.pushBack(frame);
	}
	;
	//* 根据精灵帧对象创建动画对象 */
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);    // 循环播放
	animation->setDelayPerUnit(0.04f);  // 每帧播放间隔

	/* 创建动画动作 */
	Animate* animate = Animate::create(animation);

	/* 精灵执行动作 */
	m_sprite->runAction(animate);
}

void Player::setViewPointByPlayer() {
	if (m_sprite == NULL) {
		return;
	}
	Layer* parent = (Layer*)getParent();

	/* 屏幕大小 */
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/* 主角坐标 */
	Point spritePos = getPosition();

	/* 如果主角坐标小于屏幕的一半，则取屏幕中点坐标，否则取主角的坐标 */
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	/* 如果X、Y的坐标大于右上角的极限值，则取极限值的坐标（极限值是指不让地图超出
	屏幕造成出现黑边的极限坐标） */
	x = std::min(x, p1->getWidth() - visibleSize.width / 2);
	y = std::min(y, p1->getHeight() - visibleSize.height / 2);

	/* 目标点 */
	Point destPos = Point(x, y);

	/* 屏幕中点 */
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	/* 计算屏幕中点和所要移动的目的点之间的距离 */
	Point viewPos = centerPos - destPos;

	parent->setPosition(viewPos);
}

int Player::getHp(){
	return myHp->GetStatus();
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
	isOver();
	CallFunc* callfunc = CallFunc::create([&](){
		/* 恢复状态 */
		rollBack();
	});

	/* 执行动作，碰撞到障碍物时的反弹效果 */
	auto actions = Sequence::create(jumpBy, callfunc, NULL);
	this->runAction(actions);
	FlowWord* flowWord = FlowWord::create();
	this->addChild(flowWord);
	flowWord->showWord("oh no!", m_sprite->getPosition());
}

void Player::doOperationfood(Point tiledPos){
	/* 从障碍物层清除当前格子的物体 */
	TMXLayer* barrier = m_map->getLayer("barrier");
	barrier->removeTileAt(tiledPos);
	Score += 1;
}
void Player::doOperationwin(){
	/* 取得格子的win属性值，判断是否为true，如果是，则游戏胜利，跳转到胜利场景 */
	Score = 0;
	chance = 3;
	myHp->InitStatus(100);
	myHp->Notify();
	Director::getInstance()->replaceScene(WinScene::createScene());
}

void Player::setTagPosition(int x, int y) {
	/* -----------------判断前面是否不可通行---------------- */
	/* 取主角前方的坐标 */
	Size spriteSize = m_sprite->getContentSize();
	Point dstPos = Point(x + spriteSize.width / 2, y);

	/*对每帧都实例化一个回滚类对象，用于存储状态*/
	data[frameCount] = new rollBackData(Point(x, y), Score);
	frameCount++;

	/* 获得当前主角前方坐标在地图中的格子位置 */
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));
	/* 获取地图格子的唯一标识 */
	int tiledGid = meta->getTileGIDAt(tiledPos);
	/* 不为0，代表存在这个格子 */
	if (tiledGid != 0) {
		/*
		获取该地图格子的所有属性，目前我们只有一个Collidable属性
		格子是属于meta层的，但同时也是属于整个地图的，所以在获取格子的所有属性
		时，通过格子唯一标识在地图中取得
		*/

		Value properties = m_map->getPropertiesForGID(tiledGid);
		ValueMap propertiesMap = properties.asValueMap();
		context(propertiesMap, tiledPos);
	}

	Entity::setTagPosition(x, y);

	/* 以主角为中心移动地图 */
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

	/* Cocos2d-x的默认Y坐标是由下至上的，所以要做一个相减操作 */
	int y = (700 - pos.y) / tiledSize.height;

	/* 格子坐标从零开始计算 */
	if (x > 0) {
		x -= 1;
	}
	if (y > 0) {
		y -= 0;
	}

	return Point(x, y);
}

void Player::rollBack(){
	/*回退到两秒以前的状态*/
	int t = frameCount - 60 * 2;
	/*如果距离游戏开始不到两秒，则回退到0秒的状态*/
	if (t < 0)
		t = 0;

	/*如果还有机会或血，则回退*/
	if (chance > 0 && myHp->GetStatus() > 0)
	{
		Score = data[t]->getScore();
		Entity::setTagPosition(data[t]->getPointx(), data[t]->getPointy());
		switch (Score % 6)
		{
		case 0:
			myHp->SetStatus(25);
			myHp->Notify();
			break;
		case 1:
			myHp->SetStatus(25);
			myHp->Notify();
			if (data[frameCount - 1]->getPointx() * 2 <= p1->getWidth()){
				Entity::setTagPosition(data[frameCount - 1]->getPointx() * 2, data[frameCount - 1]->getPointy());
			}
			else {
				Entity::setTagPosition(p1->getWidth() - 210, data[frameCount - 1]->getPointy());
			}
			break;
		case 2:
			myHp->SetStatus(50);
			myHp->Notify();
			Entity::setTagPosition(data[frameCount - 1]->getPointx() / 2, data[frameCount - 1]->getPointy());
			break;
		case 3:
			myHp->SetStatus(50);
			myHp->Notify();
			break;
		case 4:
			Entity::setTagPosition(p1->getWidth() - 210, data[frameCount - 1]->getPointy());
			break;
		case 5:
			myHp->SetStatus(25);
			myHp->Notify();
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
	if (chance == 0 || myHp->GetStatus() <= 0)
	{
		/*机会用完则展示失败场景*/
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LoseScene::createScene()));

		/*重置相关数据*/
		memset(data, 0, sizeof(data));
		frameCount = 0;
		Score = 0;
		myHp->InitStatus(100);
		myHp->Notify();
	}
	else if (chance < 0){
		/*点击try again后恢复机会数*/
		chance = 3;
		myHp->InitStatus(100);
		myHp->Notify();
	}
}

void Player::resetData() {
	if (isJumping) {
		isJumping = false;
	}
}

class Strategy : public Entity {
public:
	Player *player;
	virtual void doOperation(int Score, Sprite* m_sprite, FlowWord* flowWord) {
	}
};
class Operation0 : public Strategy, public Player{
	void doOperation(int Score, Sprite* m_sprite, FlowWord* flowWord) {
		Collidables* collidables = new CollidableOne();
		Score = collidables->change(Score);
		string t = collidables->getInfo().c_str();
		const char* tmp = t.c_str();
		flowWord->showWord(tmp, m_sprite->getPosition());
	}
};
class Operation1 : public Strategy{
	void doOperation(int Score, Sprite* m_sprite, FlowWord* flowWord) {
		Collidables* collidables = new CollidableTwo();
		string t = collidables->getInfo().c_str();
		const char* tmp = t.c_str();
		flowWord->showWord(tmp, m_sprite->getPosition());
	}
};
class Operation2 : public Strategy{
	void doOperation(int Score, Sprite* m_sprite, FlowWord* flowWord) {
		Collidables* collidables = new CollidableThree();
		string t = collidables->getInfo().c_str();
		const char* tmp = t.c_str();
		flowWord->showWord(tmp, m_sprite->getPosition());
	}
};
class Operation3 : public Strategy{
	void doOperation(int Score, Sprite* m_sprite, FlowWord* flowWord) {
		Collidables* collidables = new CollidableOne();
		collidables = new Collidable1(collidables);
		Score = collidables->change(Score);
		string t = collidables->getInfo().c_str();
		const char* tmp = t.c_str();
		flowWord->showWord(tmp, m_sprite->getPosition());
	}
};
class Operation4 : public Strategy{
	void doOperation(int Score, Sprite* m_sprite, FlowWord* flowWord) {
		Collidables* collidables = new CollidableTwo();
		collidables = new Collidable2(collidables);
		string t = collidables->getInfo().c_str();
		const char* tmp = t.c_str();
		flowWord->showWord(tmp, m_sprite->getPosition());
	}
};
class Operation5 : public Strategy{
	void doOperation(int Score, Sprite* m_sprite, FlowWord* flowWord) {
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
	Context(int Score, Sprite* m_sprite, FlowWord* flowWord){

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
			this->strategy->doOperation(Score, m_sprite, flowWord);
			break;
		case 1:
			this->strategy = op1;
			this->strategy->doOperation(Score, m_sprite, flowWord);
			break;
		case 2:
			this->strategy = op2;
			this->strategy->doOperation(Score, m_sprite, flowWord);
			break;
		case 3:
			this->strategy = op3;
			this->strategy->doOperation(Score, m_sprite, flowWord);
			break;
		case 4:
			this->strategy = op4;
			this->strategy->doOperation(Score, m_sprite, flowWord);
			break;
		case 5:
			this->strategy = op5;
			this->strategy->doOperation(Score, m_sprite, flowWord);
			break;
		}
	}

	Strategy *strategy;
};

void Player::randomEvent()
{
	FlowWord* flowWord = FlowWord::create();
	this->addChild(flowWord);
	/*根据当前分数对6求模获取相应碰撞事件*/

	Context context(Score, m_sprite, flowWord);

}
