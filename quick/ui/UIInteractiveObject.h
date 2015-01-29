#ifndef __UIINTERACTIVEOBJECT
#define __UIINTERACTIVEOBJECT

#include <string>
#include "UIDisplayObject.h"
#include "UINameSpace.h"

NS_UI_BEGIN

class UIInteractiveObject : public UIDisplayObject {
public:
	UIInteractiveObject();
	virtual ~UIInteractiveObject();
public:
	bool getTouchEnabled() const;
	void setTouchEnabled(bool value);
protected:
	bool _touchEnabled;
};

NS_UI_END

#endif