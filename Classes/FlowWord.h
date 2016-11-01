/*
    文件名：    FlowWord.h
    描　述：    文字飘动效果
    创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)
*/

#ifndef _FlowWord_H_
#define _FlowWord_H_

#include "cocos2d.h"
USING_NS_CC;

class FlowWord : public Node {
public:
    CREATE_FUNC(FlowWord);
    virtual bool init();

public:
	void showWord(const char* text, Point pos);
private:
	Label* m_textLab;
};

#endif