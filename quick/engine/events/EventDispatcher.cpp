#include <iostream>
#include <algorithm>

#include "EventDispatcher.h"

NS_QUICK_EVENTS_BEGIN

///////////////////////////////////////////////////////////////////////////////////

Event::Event() {
		
}

Event::Event(std::string type)
	: _type(type)
{
		
}

Event::~Event() {
		
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

Function::Function()
	:_called(false)
{
		
}

Function::~Function() {
		
}

void Function::call() {
	std::cout << "Function called...\n";
	_called = true;
}

bool Function::hasCalled() const {
	return _called;
}

///////////////////////////////////////////////////////////////////////////////////

EventDispatcher::EventDispatcher() {
		
}

EventDispatcher::~EventDispatcher() {

}

void
EventDispatcher::addEventListener(std::string type, Function *callback) {
	_citMap it = _eventListenersMap.find(type);
	if (it == _eventListenersMap.end()) {
		_tVec *temp = new std::vector<Function*>();
		_eventListenersMap[type] = temp;
	}
	_tVec *vec = _eventListenersMap[type];
	_itVec itv = std::find(vec->begin(), vec->end(), callback);
	if (itv == vec->end()) {
		vec->push_back(callback);
	}
}

bool
EventDispatcher::dispatchEvent(Event *evt) {
	evt->setTarget(this);
	std::string type = evt->getType();
	_citMap it = _eventListenersMap.find(type);
	if (it == _eventListenersMap.end()) {
		return false;
	}
	_tVec *listeners = _eventListenersMap[type];
	for (_itVec vit = listeners->begin(); vit != listeners->end(); ++vit) {
		Function *cb = *vit;
		cb->call();
	}
	return true;
}

bool EventDispatcher::hasEventListener(std::string type) const {
	_citMap it = _eventListenersMap.find(type);
	return (it != _eventListenersMap.end());
}

int EventDispatcher::getEventListenerCount(std::string type) {
	_citMap it = _eventListenersMap.find(type);
	if (it == _eventListenersMap.end()) {
		return 0;
	}
	_tVec *vec = _eventListenersMap[type];
	return vec->size();
}

void
EventDispatcher::removeEventListener(std::string type, Function *callback) {
	_citMap it = _eventListenersMap.find(type);
	if (it == _eventListenersMap.end()) {
		return;
	}
	_tVec *vec = _eventListenersMap[type];
	_itVec it_remove = std::remove(vec->begin(), vec->end(), callback);
	vec->erase(it_remove);
}

void EventDispatcher::removeEventListener(std::string type) {
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

///////////////////////////////////////////////////////////////////////////////////

NS_QUICK_EVENTS_END