
#include "DisplayObjectContainer.h"

#include <algorithm>

NS_QUICK_DISPLAY_BEGIN

///====public...
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

const DisplayObject *
DisplayObjectContainer::addChild(DisplayObject *child) {
	_itChildrenList it = std::find(_childrenList.begin(), _childrenList.end(), child);
	if (it != _childrenList.end()) {
		return child;
	}
	_childrenList.push_back(child);
	++_numChildren;
	return child;
}

const DisplayObject *
DisplayObjectContainer::addChildAt(DisplayObject *child, int index) {
	_itChildrenList it = std::find(_childrenList.begin(), _childrenList.end(), child);
	if (it != _childrenList.end()) {
		return child;
	}
	if (index < 0) {
		return child;
	}
	int i = 0;
	bool inserted = false;
	for (_itChildrenList it = _childrenList.begin(); it != _childrenList.end(); ++it) {
		if (i++ == index) {
			inserted = true;
			_childrenList.insert(it, child);
			break;
		}
	}
	if (!inserted) {
		_childrenList.push_back(child);
	}
	return child;
}

///====protected...


NS_QUICK_DISPLAY_END
