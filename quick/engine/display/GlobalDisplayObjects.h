#ifndef __GLOBALDISPLAYOBJECTS
#define __GLOBALDISPLAYOBJECTS

#include <unordered_map>
#include <typeinfo>
#include "DisplayObject.h"
#include "../NameSpace.h"

NS_QUICK_DISPLAY_BEGIN

class GlobalDisplayObjects {
public:
	static void add(DisplayObject *obj);
	static void	remove(DisplayObject *obj);
	static DisplayObject * getDisplayObjectByUID(int uid);

	template<typename T>
	static T * TgetDisplayObjectByUID(int uid) {
		DisplayObject *obj = getDisplayObjectByUID(uid);
		if (!obj) {
			return nullptr;
		}
		if (typeid(*obj) == typeid(T)) {
			return static_cast<T*>(obj);
		}
		return nullptr;
	}
private:
	static std::unordered_map<int, DisplayObject*> _allDisplayObjects;
};

NS_QUICK_DISPLAY_END

#endif