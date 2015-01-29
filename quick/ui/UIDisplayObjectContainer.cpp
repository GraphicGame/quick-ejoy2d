
#include "UIDisplayObjectContainer.h"
#include "UINameSpace.h"

NS_UI_BEGIN

UIDisplayObjectContainer::UIDisplayObjectContainer() {
	
}

UIDisplayObjectContainer::~UIDisplayObjectContainer() {

}

bool UIDisplayObjectContainer::getTouchChildren() const {
	return _touchChildren;
}

void UIDisplayObjectContainer::setTouchChildren(bool value) {
	_touchChildren = value;
}

int UIDisplayObjectContainer::getChildrenCount() const {
	return _numChildren;
}

void UIDisplayObjectContainer::addNumChildren(int count) {
	_numChildren += count;
}

void UIDisplayObjectContainer::setNumChildren(int count) {
	_numChildren = count;
}

NS_UI_END
