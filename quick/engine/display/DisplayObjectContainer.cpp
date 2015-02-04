
#include "DisplayObjectContainer.h"

#include <algorithm>

NS_QUICK_DISPLAY_BEGIN

///====public...
DisplayObjectContainer::DisplayObjectContainer()
:_childrenTouchEnabled(false), _numChildren(0)
{
	
}

DisplayObjectContainer::~DisplayObjectContainer() {
	_childrenList.clear();
}

bool DisplayObjectContainer::getChildrenTouchEnabled() const {
	return _childrenTouchEnabled;
}

void DisplayObjectContainer::setChildrenTouchEnabled(bool value) {
	_childrenTouchEnabled = value;
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
	if (index < 0) {
		return child;
	}
	_itChildrenList it = std::find(_childrenList.begin(), _childrenList.end(), child);
	if (it != _childrenList.end()) {
		return child;
	}
	int i = 0;
	bool inserted = false;
	for (_itChildrenList it = _childrenList.begin(); it != _childrenList.end(); ++it) {
		if (i++ == index) {
			inserted = true;
			_childrenList.insert(it, child);
			++_numChildren;
			break;
		}
	}
	if (!inserted) {
		_childrenList.push_back(child);
		++_numChildren;
	}
	return child;
}

bool DisplayObjectContainer::contains(const DisplayObject *child) const {
	_constItChildrenList it = std::find(_childrenList.begin(), _childrenList.end(), child);
	return (it != _childrenList.end());
}

DisplayObject*
DisplayObjectContainer::getChildAt(int index) {
	int i = 0;
	for (_itChildrenList it = _childrenList.begin(); it != _childrenList.end(); ++it) {
		if (i++ == index) {
			return *it;
		}
	}
	return nullptr;
}

DisplayObject*
DisplayObjectContainer::getChildByName(std::string name) {
	for (_itChildrenList it = _childrenList.begin(); it != _childrenList.end(); ++it) {
		if ((*it)->getName() == name) {
			return *it;
		}
	}
	return nullptr;
}

int DisplayObjectContainer::getChildIndex(DisplayObject *child) {
	int i = 0;
	for (_itChildrenList it = _childrenList.begin(); it != _childrenList.end(); ++it) {
		if ((*it) == child) {
			return i;
		}
		++i;
	}
	return -1;
}

void
DisplayObjectContainer::getObjectsUnderPoint(const quick::geom::Point &point, std::vector<DisplayObject*> &outVector) {
	//@to do...
}

DisplayObject *
DisplayObjectContainer::removeChild(DisplayObject *child) {
	_childrenList.remove(child);
	if (--_numChildren < 0)
		_numChildren = 0;
	return child;
}

DisplayObject *
DisplayObjectContainer::removeChildAt(int index) {
	int i = 0;
	for (_itChildrenList it = _childrenList.begin(); it != _childrenList.end(); ++it) {
		if (i == index) {
			return removeChild(*it);
		}
	}
	return nullptr;
}

void
DisplayObjectContainer::setChildIndex(DisplayObject *child, int index) {
	_itChildrenList it = std::find(_childrenList.begin(), _childrenList.end(), child);
	if (it == _childrenList.end()) {
		return;
	}
	_childrenList.remove(child);
	int i = 0;
	_itChildrenList targetPos;
	for (_itChildrenList it = _childrenList.begin(); it != _childrenList.end(); ++it) {
		if (i++ == index) {
			targetPos = it;
			break;
		}
	}
	_childrenList.insert(targetPos, child);
}

void
DisplayObjectContainer::swapChildren(DisplayObject *child1, DisplayObject *child2) {
	int child1Index = getChildIndex(child1);
	int child2Index = getChildIndex(child2);
	setChildIndex(child1, child2Index);
	setChildIndex(child2, child1Index);
}

void
DisplayObjectContainer::swapChildrenAt(int index1, int index2) {
	DisplayObject *child1 = getChildAt(index1);
	DisplayObject *child2 = getChildAt(index2);
	setChildIndex(child1, index2);
	setChildIndex(child2, index1);
}

///====protected...


NS_QUICK_DISPLAY_END
