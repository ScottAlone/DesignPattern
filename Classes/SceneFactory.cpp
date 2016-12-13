#include "SceneFactory.h"


SceneFactory::SceneFactory(){
}


SceneFactory::~SceneFactory(){
}


FactoryWin::FactoryWin(){
}


FactoryWin::~FactoryWin(){
}

FactoryLose::FactoryLose(){
}


FactoryLose::~FactoryLose(){
}


ProductWin* FactoryWin::createProduct(){
	ProductWin* temp = new ProductWin();
	return temp;
}

ProductLose* FactoryLose::createProduct(){
	ProductLose* temp = new ProductLose();
	return temp;
}