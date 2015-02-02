#include "GlobalDisplayObjects.h"

NS_QUICK_DISPLAY_BEGIN

std::unordered_map<int, DisplayObject*> GlobalDisplayObjects::_allDisplayObjects;

void GlobalDisplayObjects::add(DisplayObject *object) {
	int uid = object->getUID();
	std::unordered_map<int, DisplayObject*>::iterator it = _allDisplayObjects.find(uid);
	if (it != _allDisplayObjects.end()) {
		return;
	}
	_allDisplayObjects.insert(std::make_pair(uid, object));
}

void GlobalDisplayObjects::remove(DisplayObject *object) {
	int uid = object->getUID();
	_allDisplayObjects.erase(uid);
}

DisplayObject *
GlobalDisplayObjects::getDisplayObjectByUID(int uid) {
	std::unordered_map<int, DisplayObject*>::iterator it = _allDisplayObjects.find(uid);
	if (it != _allDisplayObjects.end()) {
		return it->second;
	}
	return nullptr;
}

NS_QUICK_DISPLAY_END