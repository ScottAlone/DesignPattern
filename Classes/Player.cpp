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

	/* 地图方块数量 */
	Size mapTiledNum = m_map->getMapSize();

	/* 地图单个格子大小 */
	Size tiledSize = m_map->getTileSize();

	/*地图大小 */
	Size mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);

	/* 屏幕大小 */
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/* 主角坐标 */
	Point spritePos = getPosition();

	/* 如果主角坐标小于屏幕的一半，则取屏幕中点坐标，否则取主角的坐标 */
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	/* 如果X、Y的坐标大于右上角的极限值，则取极限值的坐标（极限值是指不让地图超出
	屏幕造成出现黑边的极限坐标） */
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	/* 目标点 */
	Point destPos = Point(x, y);

	/* 屏幕中点 */
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	/* 计算屏幕中点和所要移动的目的点之间的距离 */
	Point viewPos = centerPos - destPos;

	parent->setPosition(viewPos);
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

		if (propertiesMap.find("Collidable") != propertiesMap.end())
		{
			/* 取得格子的Collidable属性值 */
			Value prop = propertiesMap.at("Collidable");
			/* 判断Collidable属性是否为true，如果是，则不让玩家移动 */
			if (prop.asString().compare("true") == 0 && isJumping == false) {
				isJumping = true;

				auto jumpBy = JumpBy::create(0.5f, Point(-100, 0), 80, 1);
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
				//Score = 0;

				//stopAllActions();	/* 先停止所有正在执行的动作 */
				//resetData();		/* 重置数据 */
				//TMXLayer* barrier = m_map->getLayer("barrier");
				//barrier->removeTileAt(tiledPos);
				//removeChild(this, true);
				isOver();
			}
		}
		if (propertiesMap.find("food") != propertiesMap.end())
		{
			/* 取得格子的food属性值，判断是否为true，如果是，则让格子上的物体消失 */
			Value prop = properties.asValueMap().at("food");
			if (prop.asString().compare("true") == 0) {
				/* 从障碍物层清除当前格子的物体 */
				TMXLayer* barrier = m_map->getLayer("barrier");
				barrier->removeTileAt(tiledPos);
				Score += 1;
			}
		}

		if (propertiesMap.find("win") != propertiesMap.end())
		{
			/* 取得格子的food属性值，判断是否为true，如果是，则让格子上的物体消失 */
			Value prop = properties.asValueMap().at("win");
			if (prop.asString().compare("true") == 0) {
				/* 取得格子的win属性值，判断是否为true，如果是，则游戏胜利，跳转到胜利场景 */
				Director::getInstance()->replaceScene(WinScene::createScene());
			}
		}
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

	/*如果还有一次机会，则回退*/
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
		/*机会用完则展示失败场景*/
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LoseScene::createScene()));

		/*重置相关数据*/
		memset(data, 0, sizeof(data));
		frameCount = 0;
		Score = 0;
	}
	else if (chance < 0)
		/*点击try again后恢复机会数*/
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
