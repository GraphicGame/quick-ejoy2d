#ifndef __EVENTDISPATCHER
#define __EVENTDISPATCHER

#include <string>
#include <vector>
#include <map>

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

class EventListenerCallback {
public:
	EventListenerCallback();
	~EventListenerCallback();
public:
	void call();
	bool hasCalled() const;
private:
	bool _called;
};

class EventDispatcher {
public:
	EventDispatcher();
	virtual ~EventDispatcher();
public:
	void addEventListener(std::string type, EventListenerCallback *callback);
	bool dispatchEvent(Event *evt);
	bool hasEventListener(std::string type) const;
	int  getEventListenerCount(std::string type);
	void removeEventListener(std::string type, EventListenerCallback *callback);
	void removeEventListener(std::string type);
	void removeAllEventListener();
private:
	std::map<std::string, std::vector<EventListenerCallback*>* > _eventListenersMap;

	typedef std::map<std::string, std::vector<EventListenerCallback*>* >::const_iterator _citMap;
	typedef std::vector<EventListenerCallback*>::iterator _itVec;
	typedef std::vector<EventListenerCallback*> _tVec;
};

NS_QUICK_EVENTS_END

#endif