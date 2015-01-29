#include <iostream>
#include <algorithm>

#include "UIEventDispatcher.h"

NS_UI_BEGIN

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

const UIEventDispatcher * Event::getTarget() const {
	return _target;
}

void Event::setTarget(UIEventDispatcher *target) {
	_target = target;
}

///////////////////////////////////////////////////////////////////////////////////

EventListenerCallback::EventListenerCallback()
	:_called(false)
{
		
}

EventListenerCallback::~EventListenerCallback() {
		
}

void EventListenerCallback::call() {
	std::cout << "EventListenerCallback called...\n";
	_called = true;
}

bool EventListenerCallback::hasCalled() const {
	return _called;
}

///////////////////////////////////////////////////////////////////////////////////

UIEventDispatcher::UIEventDispatcher() {
		
}

UIEventDispatcher::~UIEventDispatcher() {

}

void
UIEventDispatcher::addEventListener(std::string type, EventListenerCallback *callback) {
	_citMap it = _eventListenersMap.find(type);
	if (it == _eventListenersMap.end()) {
		_tVec *temp = new std::vector<EventListenerCallback*>();
		_eventListenersMap[type] = temp;
	}
	_tVec *vec = _eventListenersMap[type];
	_itVec itv = std::find(vec->begin(), vec->end(), callback);
	if (itv == vec->end()) {
		vec->push_back(callback);
	}
}

bool
UIEventDispatcher::dispatchEvent(Event *evt) {
	evt->setTarget(this);
	std::string type = evt->getType();
	_citMap it = _eventListenersMap.find(type);
	if (it == _eventListenersMap.end()) {
		return false;
	}
	_tVec *listeners = _eventListenersMap[type];
	for (_itVec vit = listeners->begin(); vit != listeners->end(); ++vit) {
		EventListenerCallback *cb = *vit;
		cb->call();
	}
	return true;
}

bool UIEventDispatcher::hasEventListener(std::string type) const {
	_citMap it = _eventListenersMap.find(type);
	return (it != _eventListenersMap.end());
}

int UIEventDispatcher::getEventListenerCount(std::string type) {
	_citMap it = _eventListenersMap.find(type);
	if (it == _eventListenersMap.end()) {
		return 0;
	}
	_tVec *vec = _eventListenersMap[type];
	return vec->size();
}

void
UIEventDispatcher::removeEventListener(std::string type, EventListenerCallback *callback) {
	_citMap it = _eventListenersMap.find(type);
	if (it == _eventListenersMap.end()) {
		return;
	}
	_tVec *vec = _eventListenersMap[type];
	_itVec it_remove = std::remove(vec->begin(), vec->end(), callback);
	vec->erase(it_remove);
}

void UIEventDispatcher::removeEventListener(std::string type) {
	_citMap it = _eventListenersMap.find(type);
	if (it == _eventListenersMap.end()) {
		return;
	}
	_tVec *vec = _eventListenersMap[type];
	vec->clear();
	vec->erase(vec->begin(), vec->end());
}

void UIEventDispatcher::removeAllEventListener() {
	_eventListenersMap.clear();
}

///////////////////////////////////////////////////////////////////////////////////

NS_UI_END