#ifndef __DISPLAYOBJECTCONTAINER
#define __DISPLAYOBJECTCONTAINER

#include "InteractiveObject.h"
#include "../NameSpace.h"
#include "../geom/Point.h"

#include <string>
#include <list>

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
	bool contains(const DisplayObject *child) const;
	DisplayObject * getChildAt(int index);
	DisplayObject * getChildByName(std::string name);
	int getChildIndex(DisplayObject *child);
	void getObjectsUnderPoint(const quick::geom::Point &point, std::vector<DisplayObject*> &outVector);
	DisplayObject * removeChild(DisplayObject *child);
	DisplayObject * removeChildAt(int index);
	void setChildIndex(DisplayObject *child, int index);
	void swapChildren(DisplayObject *child1, DisplayObject *child2);
	void swapChildrenAt(int index1, int index2);

protected:
	bool _childrenTouchEnabled;
	int _numChildren;
	std::list<DisplayObject*> _childrenList;

	typedef std::list<DisplayObject*>::iterator _itChildrenList;
	typedef std::list<DisplayObject*>::const_iterator _constItChildrenList;
};

NS_QUICK_DISPLAY_END


#endif