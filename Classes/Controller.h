#ifndef _Controller_H_
#define _Controller_H_

#include "cocos2d.h"
#include "ControllerListener.h"

using namespace cocos2d;
class Controller : public Node
{
public:
	/* ÉèÖÃ¼àÌı¶ÔÏó */
	void setControllerListener(ControllerListener* controllerListener);

protected:
	ControllerListener* m_controllerListener;
};

#endif