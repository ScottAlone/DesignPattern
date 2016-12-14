#ifndef _SCENEFACTORY_H_
#define _SCENEFACTORY_H_

#include "cocos2d.h"
#include "SceneProduct.h"

USING_NS_CC;

class SceneFactory {
public:
	SceneFactory();

	virtual ~SceneFactory();

public:
	virtual SceneProduct* createProduct() = 0;

};

class FactoryWin :public SceneFactory{

public:
	FactoryWin();

	~FactoryWin();

public:
	ProductWin* createProduct();

};

class FactoryLose :public SceneFactory{

public:
	FactoryLose();

	~FactoryLose();

public:
	ProductLose* createProduct();

};

class FactoryHelp :public SceneFactory{

public:
	FactoryHelp();

	~FactoryHelp();

public:
	SceneProduct* createProduct();

};

class FactoryGate :public SceneFactory{

public:
	FactoryGate();

	~FactoryGate();

public:
	ProductGate* createProduct();

};

class FactoryStart :public SceneFactory{

public:
	FactoryStart();

	~FactoryStart();

public:
	ProductStart* createProduct();

};

#endif