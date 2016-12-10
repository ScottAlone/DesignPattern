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
//Ѫ��  
class HP
{
public:
	HP() {}
	virtual ~HP() {}
	void Attach(Observer *observer) { m_observers.push_back(observer); }     //���ӹ۲���  
	void Remove(Observer *observer) { m_observers.remove(observer); }        //�Ƴ��۲���  
	void Notify() //֪ͨ�۲���  
	{
		list<Observer*>::iterator iter = m_observers.begin();
		for (; iter != m_observers.end(); iter++)
			(*iter)->Update();
	}
	virtual void InitStatus(int s) { hp = s; }
	virtual void SetStatus(int s) { hp = hp - s; } //����״̬  
	virtual int GetStatus() { return hp; }    //���״̬  
private:
	list<Observer* > m_observers; //�۲�������  
protected:
	int hp; //״̬  
};
//����Ѫ����  
class MyHp : public HP
{
public:
	MyHp(){}
	~MyHp() {}
	void SetStatus(int s) { hp = hp - s; } //��������״̬��Ϣ  
	int GetStatus() { return hp; }
};
//����۲���  
class ObserverHp : public Observer
{
private:
	HP *m_hp;   //�۲��Ѫ��
public:
	ObserverHp(HP *hp) : m_hp(hp) {}
	~ObserverHp() {}
	void Update()  //��ø���״̬  
	{
		int hp = m_hp->GetStatus();
	}
};
#endif