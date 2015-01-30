#ifndef __TOUCHEVENT
#define __TOUCHEVENT

#include <string>
#include "EventDispatcher.h"
#include "../NameSpace.h"

NS_QUICK_EVENTS_BEGIN

class TouchEvent : public Event {
public:
	explicit TouchEvent(std::string type);
	~TouchEvent();
public:
	float getWorldX() const;
	float getWorldY() const;

	float getLocalX() const;
	float getLocalY() const;

	bool isPressed() const;
protected:
	TouchEvent();
private:
	float _worldX, _worldY;
	float _localX, _localY;
	bool _isPressed;
};		

NS_QUICK_EVENTS_END

#endif