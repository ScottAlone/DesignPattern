#ifndef _FlowWord_H_
#define _FlowWord_H_

#include "cocos2d.h"
USING_NS_CC;

class FlowWord : public Node {
public:
	static FlowWord* create();
    virtual bool init();

public:
	void showWord(const char* text, Point pos);
private:
	Label* m_textLab;
};

#endif