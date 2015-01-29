#include <iostream>
#include <algorithm>

#include "UIEventDispatcher.h"

namespace ui {

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
		_cit_map it = _event_listeners_map.find(type);
		if (it == _event_listeners_map.end()) {
			_t_vec *temp = new std::vector<EventListenerCallback*>();
			_event_listeners_map[type] = temp;
		}
		_t_vec *vec = _event_listeners_map[type];
		_it_vec itv = std::find(vec->begin(), vec->end(), callback);
		if (itv == vec->end()) {
			vec->push_back(callback);
		}
	}

	bool
	UIEventDispatcher::dispatchEvent(Event *evt) {
		evt->setTarget(this);
		std::string type = evt->getType();
		_cit_map it = _event_listeners_map.find(type);
		if (it == _event_listeners_map.end()) {
			return false;
		}
		_t_vec *listeners = _event_listeners_map[type];
		for (_it_vec vit = listeners->begin(); vit != listeners->end(); ++vit) {
			EventListenerCallback *cb = *vit;
			cb->call();
		}
		return true;
	}

	bool UIEventDispatcher::hasEventListener(std::string type) const {
		_cit_map it = _event_listeners_map.find(type);
		return (it != _event_listeners_map.end());
	}

	int UIEventDispatcher::getEventListenerCount(std::string type) {
		_cit_map it = _event_listeners_map.find(type);
		if (it == _event_listeners_map.end()) {
			return 0;
		}
		_t_vec *vec = _event_listeners_map[type];
		return vec->size();
	}

	void
	UIEventDispatcher::removeEventListener(std::string type, EventListenerCallback *callback) {
		_cit_map it = _event_listeners_map.find(type);
		if (it == _event_listeners_map.end()) {
			return;
		}
		_t_vec *vec = _event_listeners_map[type];
		_it_vec it_remove = std::remove(vec->begin(), vec->end(), callback);
		vec->erase(it_remove);
	}

	void UIEventDispatcher::removeEventListener(std::string type) {
		_cit_map it = _event_listeners_map.find(type);
		if (it == _event_listeners_map.end()) {
			return;
		}
		_t_vec *vec = _event_listeners_map[type];
		vec->clear();
		vec->erase(vec->begin(), vec->end());
	}

	void UIEventDispatcher::removeAllEventListener() {
		_event_listeners_map.clear();
	}

	///////////////////////////////////////////////////////////////////////////////////

}