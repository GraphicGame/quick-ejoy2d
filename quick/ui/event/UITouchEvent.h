#ifndef __UITOUCHEVENT
#define __UITOUCHEVENT

#include <string>
#include "UIEventDispatcher.h"
#include "UINameSpace.h"

NS_UI_EVENT_BEGIN

class UITouchEvent : public Event {
public:
	explicit UITouchEvent(std::string type);
	~UITouchEvent();
public:
	float getWorldX() const;
	float getWorldY() const;

	float getLocalX() const;
	float getLocalY() const;

	bool isPressed() const;
protected:
	UITouchEvent();
private:
	float _worldX, _worldY;
	float _localX, _localY;
	bool _isPressed;
};		

NS_UI_EVENT_END

#endif