
#include "UITouchEvent.h"

NS_UI_EVENT_BEGIN
		
UITouchEvent::UITouchEvent() {
			
}

UITouchEvent::UITouchEvent(std::string type) 
	: Event(type)
{
			
}

UITouchEvent::~UITouchEvent() {
			
}

float UITouchEvent::getWorldX() const {
	return _worldX;
}

float UITouchEvent::getWorldY() const {
	return _worldY;
}

float UITouchEvent::getLocalX() const {
	return _localX;
}

float UITouchEvent::getLocalY() const {
	return _localY;
}

bool UITouchEvent::isPressed() const {
	return _isPressed;
}

NS_UI_EVENT_END
