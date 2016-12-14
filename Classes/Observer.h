#ifndef _Observer_H_
#define _Observer_H_

#include <list>
using namespace std;
class Observer
{
public:
	Observer() {}
	virtual ~Observer() {}
	virtual void Update() {}
};
//血量  
class HP
{
public:
	HP() {}
	virtual ~HP() {}
	void Attach(Observer *observer) { //添加观察者
		m_observers.push_back(observer); 
	}      
	void Remove(Observer *observer) { //移除观察者  
		m_observers.remove(observer); 
	}        
	void Notify() //通知观察者  
	{
		list<Observer*>::iterator iter = m_observers.begin();
		for (; iter != m_observers.end(); iter++)
			(*iter)->Update();
	}
	virtual void InitStatus(int s) { hp = s; }
	virtual void SetStatus(int s) { hp = hp - s; } //设置状态  
	virtual int GetStatus() { return hp; }    //获得状态  
private:
	list<Observer* > m_observers; //观察者链表  
protected:
	int hp; //状态  
};
//具体血量类  
class MyHp : public HP
{
public:
	MyHp(){}
	~MyHp() {}
	void SetStatus(int s) { hp = hp - s; } //具体设置状态信息  
	int GetStatus() { return hp; }
};
//具体观察者  
class ObserverHp : public Observer
{
private:
	HP *m_hp;   //观察的血量
public:
	ObserverHp(HP *hp) : m_hp(hp) {}
	~ObserverHp() {}
	void Update()  //获得更新状态  
	{
		int hp = m_hp->GetStatus();
	}
};
#endif