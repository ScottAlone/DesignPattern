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

FactoryHelp::FactoryHelp(){
}

FactoryHelp::~FactoryHelp(){
}

FactoryGate::FactoryGate(){
}

FactoryGate::~FactoryGate(){
}


ProductWin* FactoryWin::createProduct(){
	ProductWin* temp = new ProductWin();
	return temp;
}

ProductLose* FactoryLose::createProduct(){
	ProductLose* temp = new ProductLose();
	return temp;
}

ProductHelp* FactoryHelp::createProduct(){
	ProductHelp* temp = new ProductHelp();
	return temp;
}

ProductGate* FactoryGate::createProduct(){
	ProductGate* temp = new ProductGate();
	return temp;
}

ProductStart* FactoryStart::createProduct(){
	ProductStart* temp = new ProductStart();
	return temp;
}