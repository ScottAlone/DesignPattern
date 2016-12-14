#ifndef _ThreeDirectionController_H_
#define _ThreeDirectionController_H_

#include "Controller.h"
#include "cocos2d.h"
using namespace cocos2d;

class ThreeDirectionController : public Controller {
public:
	static ThreeDirectionController* create();
	virtual bool init();
	virtual void update(float dt);

	/* ����X������ƶ��ٶ� */
	void setiXSpeed(int iSpeed);

	/* ����Y������ƶ��ٶ�*/
	void setiYSpeed(int iSpeed);

private:
	int m_iXSpeed;
	int m_iYSpeed;

	/* ע����Ļ�����¼� */
	void registeTouchEvent();
};

#endif