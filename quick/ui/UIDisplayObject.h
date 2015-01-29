#ifndef __UIDISPLAYOBJECT
#define __UIDISPLAYOBJECT

#include <string>

#include "UIEventDispatcher.h"
#include "UINameSpace.h"

NS_UI_BEGIN
class UIDisplayObject : public UIEventDispatcher {
public:
	UIDisplayObject();
	virtual ~UIDisplayObject();
public:
	const std::string& getName() const;
	void setName(std::string name);
	void setName(const char *name);

	const UIDisplayObject * getParent() const;
	virtual void setParent(UIDisplayObject *parent);

	virtual void draw();

	float getX() const;
	float getY() const;
	void setX(float x);
	void setY(float y);

	float getScale() const;
	float getScaleX() const;
	float getScaleY() const;
	void setScale(float scale);
	void setScale(float sx, float sy);
	void setScaleX(float sx);
	void setScaleY(float sy);

	float getRotation() const;
	float getRotationX() const;
	float getRotationY() const;
	void setRotation(float rotation);
	void setRotation(float rx, float ry);
	void setRotationX(float rx);
	void setRotationY(float ry);

	float getWidth() const;
	void setWidth(float w);
	float getHeight() const;
	void setHeight(float h);

	bool getVisible() const;
	void setVisible(bool visible);
protected:
	std::string _name;
	UIDisplayObject *_parent;
	float _x;
	float _y;
	float _scale, _scaleX, _scaleY;
	float _rotation, _rotationX, _rotationY;
	float _width, _height;
	bool _visible;
};
NS_UI_END

#endif