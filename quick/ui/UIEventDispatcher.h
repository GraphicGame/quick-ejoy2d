#ifndef __UIEVENTDISPATCHER
#define __UIEVENTDISPATCHER

#include <string>
#include <vector>
#include <map>

#include "UINameSpace.h"

NS_UI_BEGIN

class UIEventDispatcher;

class Event {
public:
	Event(std::string type);
	virtual ~Event();
public:
	const std::string& getType() const;
	const UIEventDispatcher * getTarget() const;
	void setTarget(UIEventDispatcher *target);
protected:
	Event();
protected:
	std::string _type;
	UIEventDispatcher *_target;
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

class UIEventDispatcher {
public:
	UIEventDispatcher();
	virtual ~UIEventDispatcher();
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

NS_UI_END

#endif