#ifndef __DISPLAYOBJECTCONTAINER
#define __DISPLAYOBJECTCONTAINER

#include "InteractiveObject.h"
#include "NameSpace.h"
#include <string>

NS_QUICK_DISPLAY_BEGIN

class DisplayObjectContainer : public InteractiveObject {
public:
	DisplayObjectContainer();
	~DisplayObjectContainer();
public:
	bool getTouchChildren() const;
	void setTouchChildren(bool value);

	int getChildrenCount() const;

	const DisplayObject * addChild(DisplayObject *child);
	const DisplayObject * addChildAt(DisplayObject *child, int index);
	bool contains(DisplayObject *child) const;
	DisplayObject * getChildAt(int index);
	DisplayObject * getChildByName(std::string name);
	int getChildIndex(DisplayObject *child);

protected:
	void addNumChildren(int count);
	void setNumChildren(int count);
protected:
	bool _touchChildren;
	int _numChildren;
};

NS_QUICK_DISPLAY_END


#endif