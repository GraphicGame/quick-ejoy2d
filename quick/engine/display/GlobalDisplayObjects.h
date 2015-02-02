#ifndef __GLOBALDISPLAYOBJECTS
#define __GLOBALDISPLAYOBJECTS

#include <unordered_map>
#include "DisplayObject.h"
#include "../NameSpace.h"

NS_QUICK_DISPLAY_BEGIN

class GlobalDisplayObjects {
public:
	static void add(DisplayObject *obj);
	static void	remove(DisplayObject *obj);
	static DisplayObject * getDisplayObjectByUID(int uid);
private:
	static std::unordered_map<int, DisplayObject*> _allDisplayObjects;
};

NS_QUICK_DISPLAY_END

#endif