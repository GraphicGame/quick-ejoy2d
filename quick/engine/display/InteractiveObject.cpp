
#include "InteractiveObject.h"

NS_QUICK_DISPLAY_BEGIN

InteractiveObject::InteractiveObject() {
		
}

InteractiveObject::~InteractiveObject() {

}

bool InteractiveObject::getTouchEnabled() const {
	return _touchEnabled;
}

void InteractiveObject::setTouchEnabled(bool value) {
	_touchEnabled = value;
}

NS_QUICK_DISPLAY_END