#include <string>
using namespace std;
#include "Collidables.h"

CollidableOne::CollidableOne(){
	info = "Score X 2!";
}

int CollidableOne::change(int score){ 
	return 2 * score; 
}

CollidableTwo::CollidableTwo(){
	info = "Go forward!";
}

int CollidableTwo::change(int position){ 
	return 2 * position; 
}

CollidableThree::CollidableThree(){
	info = "Go backward!";
}

int CollidableThree::change(int position){ 
	return 1 / 2 * position;
}

Collidable1::Collidable1(Collidables *collidables){
	this->collidables = collidables;
}
string Collidable1::getInfo(){
	return collidables->getInfo() + "? No, X 4!";
}
int Collidable1::change(int i){
	return collidables->change(i) * 2;
}

Collidable2::Collidable2(Collidables *collidables){
	this->collidables = collidables;
}
string Collidable2::getInfo(){
	return collidables->getInfo() + "? No,go win!";
}
int Collidable2::change(int i){
	return collidables->change(1000000);
}

Collidable3::Collidable3(Collidables *collidables){
	this->collidables = collidables;
}
string Collidable3::getInfo(){
	return collidables->getInfo() + "? No,go to start!";
}
int Collidable3::change(int i){
	return collidables->change(0);
}