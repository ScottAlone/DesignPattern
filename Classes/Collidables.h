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
	CollidableOne(){
		info = "Score X 2!";
	}
	int change(int score){ return 2 * score; };
};
class CollidableTwo : public Collidables   //�ϰ���2����
{
public:
	CollidableTwo(){
		info = "Go forward!";
	}
	int change(int position){ return 2 * position; };
};
class CollidableThree : public Collidables   //�ϰ���3����
{
public:
	CollidableThree(){
		info = "Go backward!";
	}
	int change(int position){ return 1/2 * position; };
};
class CollidableDecorator : public Collidables   //װ����
{
protected:
	Collidables *collidables;
};
class Collidable1 : public CollidableDecorator   //�ϰ���1��չ
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
class Collidable2 : public CollidableDecorator   //�ϰ���2��չ
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
class Collidable3 : public CollidableDecorator   //�ϰ���3��չ
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