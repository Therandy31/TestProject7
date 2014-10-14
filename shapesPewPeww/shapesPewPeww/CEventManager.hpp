#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;

class IEvent {
protected:
	string type;
public:
	IEvent() { type = ""; }
	IEvent(string type) { this->type = type; }
	string getType() { return type; }
	bool compareType(std::string type) {
		if (this->type.compare(type) == 0) {
			return true;
		}
		return false;
	}
};

class IEventable {
public:
	virtual void notify(IEvent *e) = 0;
};

class CEventManager {
private:
	list<IEventable *> subscribed;
	CEventManager();
public:
	~CEventManager();
	void subscribe(IEventable *eventable);
	void unsubscribe(IEventable *eventable);
	void post(IEvent *e);
	static CEventManager *instance();
	bool hasEventable(IEventable *eventable);
};