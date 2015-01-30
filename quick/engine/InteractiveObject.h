#ifndef __INTERACTIVEOBJECT
#define __INTERACTIVEOBJECT

#include <string>
#include "DisplayObject.h"
#include "NameSpace.h"

NS_QUICK_DISPLAY_BEGIN

class InteractiveObject : public DisplayObject {
public:
	InteractiveObject();
	virtual ~InteractiveObject();
public:
	bool getTouchEnabled() const;
	void setTouchEnabled(bool value);
protected:
	bool _touchEnabled;
};

NS_QUICK_DISPLAY_END

#endif