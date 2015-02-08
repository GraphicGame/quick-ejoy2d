#ifndef __EVENTDISPATCHER
#define __EVENTDISPATCHER

#include <string>
#include <vector>
#include <unordered_map>
#include <lua.h>

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

class EventDispatcher {
public:
	EventDispatcher();
	virtual ~EventDispatcher();
public:
	void addEventListener(const char *type, const char *funcKey);
	bool dispatchEvent(lua_State *L, const char *type);
	bool hasEventListener(const char *type) const;
	int  getEventListenerCount(const char *type);
	void removeEventListener(const char *type, const char *funcKey);
	void removeEventListener(const char *type);
	void removeAllEventListener();
private:
	void call(lua_State *L, std::string funcKey, EventDispatcher *sender);
private:
	std::unordered_map<std::string, std::vector<std::string>* > _eventListenersMap;

	typedef std::unordered_map<std::string, std::vector<std::string>* >::const_iterator _citMap;
	typedef std::vector<std::string>::iterator _itVec;
	typedef std::vector<std::string> _tVec;
};

NS_QUICK_EVENTS_END

#endif