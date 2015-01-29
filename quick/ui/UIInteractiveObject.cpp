
#include "UIInteractiveObject.h"

NS_UI_BEGIN

UIInteractiveObject::UIInteractiveObject() {
		
}

UIInteractiveObject::~UIInteractiveObject() {

}

bool UIInteractiveObject::getTouchEnabled() const {
	return _touchEnabled;
}

void UIInteractiveObject::setTouchEnabled(bool value) {
	_touchEnabled = value;
}

NS_UI_END