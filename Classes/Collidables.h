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
	CollidableOne(){
		info = "Score X 2!";
	}
	int change(int score){ return 2 * score; };
};
class CollidableTwo : public Collidables   //障碍物2基类
{
public:
	CollidableTwo(){
		info = "Go forward!";
	}
	int change(int position){ return 2 * position; };
};
class CollidableThree : public Collidables   //障碍物3基类
{
public:
	CollidableThree(){
		info = "Go backward!";
	}
	int change(int position){ return 1/2 * position; };
};
class CollidableDecorator : public Collidables   //装饰类
{
protected:
	Collidables *collidables;
};
class Collidable1 : public CollidableDecorator   //障碍物1扩展
{
public:
	Collidable1(Collidables *collidables){
		this->collidables = collidables;
	};
	string getInfo(){
		return collidables->getInfo() + "? No, X 4!";
	}
	int change(int i){
		return collidables->change(i)*2;
	}
};
class Collidable2 : public CollidableDecorator   //障碍物2扩展
{
public:
	Collidable2(Collidables *collidables){
		this->collidables = collidables;
	};
	string getInfo(){
		return collidables->getInfo() + "? No,go win!";
	}
	int change(int i){
		return collidables->change(1000000);
	}
};
class Collidable3 : public CollidableDecorator   //障碍物3扩展
{
public:
	Collidable3(Collidables *collidables){
		this->collidables = collidables;
	};
	string getInfo(){
		return collidables->getInfo() + "? No,go to start!";
	}
	int change(int i){
		return collidables->change(0);
	}
};
#endif