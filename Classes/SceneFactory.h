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

#endif