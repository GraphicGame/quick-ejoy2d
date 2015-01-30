
#include "DisplayObjectContainer.h"

NS_QUICK_DISPLAY_BEGIN

DisplayObjectContainer::DisplayObjectContainer() {
	
}

DisplayObjectContainer::~DisplayObjectContainer() {

}

bool DisplayObjectContainer::getTouchChildren() const {
	return _touchChildren;
}

void DisplayObjectContainer::setTouchChildren(bool value) {
	_touchChildren = value;
}

int DisplayObjectContainer::getChildrenCount() const {
	return _numChildren;
}

void DisplayObjectContainer::addNumChildren(int count) {
	_numChildren += count;
}

void DisplayObjectContainer::setNumChildren(int count) {
	_numChildren = count;
}

NS_QUICK_DISPLAY_END
