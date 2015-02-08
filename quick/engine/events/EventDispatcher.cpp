#include <iostream>
#include <algorithm>

#include "EventDispatcher.h"

#include <lua.h>
#include <lauxlib.h>

NS_QUICK_EVENTS_BEGIN

///////////////////////////////////////////////////////////////////////////////////

Event::Event() {
		
}

Event::Event(std::string type)
	: _type(type)
{
	
}

Event::~Event() {
	_type.clear();
	_type.swap(std::string());
	delete _target;
}

const std::string& Event::getType() const {
	return _type;
}

const EventDispatcher * Event::getTarget() const {
	return _target;
}

void Event::setTarget(EventDispatcher *target) {
	_target = target;
}

///////////////////////////////////////////////////////////////////////////////////

EventDispatcher::EventDispatcher() {
		
}

EventDispatcher::~EventDispatcher() {
	_eventListenersMap.clear();
}

void
EventDispatcher::addEventListener(const char *type, const char *callback) {
	std::string strType(type);
	std::string strCallback(callback);

	_citMap it = _eventListenersMap.find(strType);
	if (it == _eventListenersMap.end()) {
		_tVec *temp = new std::vector<std::string>();
		_eventListenersMap[strType] = temp;
	}
	_tVec *vec = _eventListenersMap[strType];
	_itVec itv = std::find(vec->begin(), vec->end(), strCallback);
	if (itv == vec->end()) {
		vec->push_back(strCallback);
	}
}

bool
EventDispatcher::dispatchEvent(lua_State *L, const char *t) {
	std::string type(t);
	_citMap it = _eventListenersMap.find(type);
	if (it == _eventListenersMap.end()) {
		return false;
	}
	_tVec *listeners = _eventListenersMap[type];
	for (_itVec vit = listeners->begin(); vit != listeners->end(); ++vit) {
		call(L, *vit, this);
	}
	return true;
}

bool EventDispatcher::hasEventListener(const char *type) const {
	std::string t(type);
	_citMap it = _eventListenersMap.find(type);
	return (it != _eventListenersMap.end());
}

int EventDispatcher::getEventListenerCount(const char *t) {
	std::string type(t);
	_citMap it = _eventListenersMap.find(type);
	if (it == _eventListenersMap.end()) {
		return 0;
	}
	_tVec *vec = _eventListenersMap[type];
	return vec->size();
}

void
EventDispatcher::removeEventListener(const char *t, const char *funcKey) {
	std::string type(t);
	std::string callback(funcKey);

	_citMap it = _eventListenersMap.find(type);
	if (it == _eventListenersMap.end()) {
		return;
	}
	_tVec *vec = _eventListenersMap[type];
	_itVec it_remove = std::remove(vec->begin(), vec->end(), callback);
	vec->erase(it_remove);
}

void EventDispatcher::removeEventListener(const char *t) {
	std::string type(t);

	_citMap it = _eventListenersMap.find(type);
	if (it == _eventListenersMap.end()) {
		return;
	}
	_tVec *vec = _eventListenersMap[type];
	vec->clear();
	vec->erase(vec->begin(), vec->end());
}

void EventDispatcher::removeAllEventListener() {
	_eventListenersMap.clear();
}

void EventDispatcher::call(lua_State *L, std::string funcKey, EventDispatcher *sender) {
	lua_getglobal(L, "__event_callback_entry_func__");
	const char *cFuncKey = funcKey.c_str();
	lua_pushstring(L, cFuncKey);
	lua_pushlightuserdata(L, sender);
	lua_pcall(L, 2, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////////

NS_QUICK_EVENTS_END