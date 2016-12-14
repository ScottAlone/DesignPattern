#ifndef _SCENEFACTORY_H_
#define _SCENEFACTORY_H_

#include "cocos2d.h"
#include "SceneProduct.h"

USING_NS_CC;

class SceneFactory {
public:
	virtual SceneProduct* createProduct() = 0;

};

class FactoryWin :public SceneFactory{
public:
	ProductWin* createProduct();

};

class FactoryLose :public SceneFactory{
public:
	ProductLose* createProduct();

};

class FactoryHelp :public SceneFactory{
public:
	ProductHelp* createProduct();

};

class FactoryGate :public SceneFactory{
public:
	ProductGate* createProduct();

};

class FactoryStart :public SceneFactory{
public:
	ProductStart* createProduct();

};

#endif