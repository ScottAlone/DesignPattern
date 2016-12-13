#ifndef _Collidables_H_
#define _Collidables_H_
#include <string>
using namespace std;
class Collidables	//�ϰ���
{
protected:
	
public:
	string info;
	virtual string getInfo(){
		return info;
	}
	virtual int change(int i) = 0;
};
class CollidableOne : public Collidables   //�ϰ���1����
{
public:
	CollidableOne();
	int change(int score);
};
class CollidableTwo : public Collidables   //�ϰ���2����
{
public:
	CollidableTwo();
	int change(int position);
};
class CollidableThree : public Collidables   //�ϰ���3����
{
public:
	CollidableThree();
	int change(int position);
};
class CollidableDecorator : public Collidables   //װ����
{
protected:
	Collidables *collidables;
};
class Collidable1 : public CollidableDecorator   //�ϰ���1��չ
{
public:
	Collidable1(Collidables *collidables);
	string getInfo();
	int change(int i);
};
class Collidable2 : public CollidableDecorator   //�ϰ���2��չ
{
public:
	Collidable2(Collidables *collidables);
	string getInfo();
	int change(int i);
};
class Collidable3 : public CollidableDecorator   //�ϰ���3��չ
{
public:
	Collidable3(Collidables *collidables);
	string getInfo();
	int change(int i);
};
#endif