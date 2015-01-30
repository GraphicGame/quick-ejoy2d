
#include "TouchEvent.h"

NS_QUICK_EVENTS_BEGIN
		
TouchEvent::TouchEvent() {
			
}

TouchEvent::TouchEvent(std::string type) 
	: Event(type)
{
			
}

TouchEvent::~TouchEvent() {
			
}

float TouchEvent::getWorldX() const {
	return _worldX;
}

float TouchEvent::getWorldY() const {
	return _worldY;
}

float TouchEvent::getLocalX() const {
	return _localX;
}

float TouchEvent::getLocalY() const {
	return _localY;
}

bool TouchEvent::isPressed() const {
	return _isPressed;
}

NS_QUICK_EVENTS_END
