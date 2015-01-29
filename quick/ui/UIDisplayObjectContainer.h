#ifndef __UIDISPLAYOBJECTCONTAINER
#define __UIDISPLAYOBJECTCONTAINER

#include "UIInteractiveObject.h"
#include "UINameSpace.h"
#include <string>

NS_UI_BEGIN

class UIDisplayObjectContainer : public UIInteractiveObject {
public:
	UIDisplayObjectContainer();
	~UIDisplayObjectContainer();
public:
	bool getTouchChildren() const;
	void setTouchChildren(bool value);

	int getChildrenCount() const;

	const UIDisplayObject * addChild(UIDisplayObject *child);
	const UIDisplayObject * addChildAt(UIDisplayObject *child, int index);
	bool contains(UIDisplayObject *child) const;
	UIDisplayObject * getChildAt(int index);
	UIDisplayObject * getChildByName(std::string name);
	int getChildIndex(UIDisplayObject *child);

protected:
	void addNumChildren(int count);
	void setNumChildren(int count);
protected:
	bool _touchChildren;
	int _numChildren;
};

NS_UI_END


#endif