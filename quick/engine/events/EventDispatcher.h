#ifndef __EVENTDISPATCHER
#define __EVENTDISPATCHER

#include <string>
#include <vector>
#include <unordered_map>

#include "../NameSpace.h"

NS_QUICK_EVENTS_BEGIN

class EventDispatcher;

class Event {
public:
	Event(std::string type);
	virtual ~Event();
public:
	const std::string& getType() const;
	const EventDispatcher * getTarget() const;
	void setTarget(EventDispatcher *target);
protected:
	Event();
protected:
	std::string _type;
	EventDispatcher *_target;
};

class Function {
public:
	Function();
	~Function();
public:
	void call();
	bool hasCalled() const;
private:
	bool _called;
	int _funcID;
};

class EventDispatcher {
public:
	EventDispatcher();
	virtual ~EventDispatcher();
public:
	void addEventListener(std::string type, Function *callback);
	bool dispatchEvent(Event *evt);
	bool hasEventListener(std::string type) const;
	int  getEventListenerCount(std::string type);
	void removeEventListener(std::string type, Function *callback);
	void removeEventListener(std::string type);
	void removeAllEventListener();
private:
	std::unordered_map<std::string, std::vector<Function*>* > _eventListenersMap;

	typedef std::unordered_map<std::string, std::vector<Function*>* >::const_iterator _citMap;
	typedef std::vector<Function*>::iterator _itVec;
	typedef std::vector<Function*> _tVec;
};

NS_QUICK_EVENTS_END

#endif