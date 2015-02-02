#ifndef __DISPLAYOBJECTCONTAINER
#define __DISPLAYOBJECTCONTAINER

#include "InteractiveObject.h"
#include "../NameSpace.h"
#include "../geom/Point.h"

#include <string>
#include <list>
#include <unordered_map>

NS_QUICK_DISPLAY_BEGIN

class DisplayObjectContainer : public InteractiveObject {
public:
	DisplayObjectContainer();
	virtual ~DisplayObjectContainer();
public:
	bool getChildrenTouchEnabled() const;
	void setChildrenTouchEnabled(bool value);

	int getChildrenCount() const;

	const DisplayObject * addChild(DisplayObject *child);
	const DisplayObject * addChildAt(DisplayObject *child, int index);

	DisplayObject * removeChild(DisplayObject *child);
	DisplayObject * removeChildAt(int index);

	DisplayObject * getChildAt(int index);
	DisplayObject * getChildByName(std::string name);
	int getChildIndex(DisplayObject *child);

	void setChildIndex(DisplayObject *child, int index);
	void swapChildren(DisplayObject *child1, DisplayObject *child2);
	void swapChildrenAt(int index1, int index2);

	bool contains(const DisplayObject *child) const;
	void getObjectsUnderPoint(const quick::geom::Point &point, std::vector<DisplayObject*> &outVector);

protected:
	bool _childrenTouchEnabled;
	int _numChildren;

	std::list<DisplayObject*> _childrenList;
	typedef std::list<DisplayObject*>::iterator _itChildrenList;
	typedef std::list<DisplayObject*>::const_iterator _constItChildrenList;
};

NS_QUICK_DISPLAY_END


#endif