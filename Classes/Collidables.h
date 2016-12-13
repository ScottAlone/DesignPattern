#ifndef _Collidables_H_
#define _Collidables_H_
#include <string>
using namespace std;
class Collidables	//障碍物
{
protected:
	
public:
	string info;
	virtual string getInfo(){
		return info;
	}
	virtual int change(int i) = 0;
};
class CollidableOne : public Collidables   //障碍物1基类
{
public:
	CollidableOne();
	int change(int score);
};
class CollidableTwo : public Collidables   //障碍物2基类
{
public:
	CollidableTwo();
	int change(int position);
};
class CollidableThree : public Collidables   //障碍物3基类
{
public:
	CollidableThree();
	int change(int position);
};
class CollidableDecorator : public Collidables   //装饰类
{
protected:
	Collidables *collidables;
};
class Collidable1 : public CollidableDecorator   //障碍物1扩展
{
public:
	Collidable1(Collidables *collidables);
	string getInfo();
	int change(int i);
};
class Collidable2 : public CollidableDecorator   //障碍物2扩展
{
public:
	Collidable2(Collidables *collidables);
	string getInfo();
	int change(int i);
};
class Collidable3 : public CollidableDecorator   //障碍物3扩展
{
public:
	Collidable3(Collidables *collidables);
	string getInfo();
	int change(int i);
};
#endif