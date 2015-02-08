#ifndef __DISPLAYOBJECT
#define __DISPLAYOBJECT

#include <string>

#include "../events/EventDispatcher.h"
#include "../NameSpace.h"
#include "DisplayObjectType.h"
using namespace quick::events;

NS_QUICK_DISPLAY_BEGIN

class DisplayObject : public EventDispatcher {
public:
	DisplayObject();
	virtual ~DisplayObject();
public:
	const std::string getName() const;
	void setName(std::string name);
	void setName(const char *name);

	const DisplayObject * getParent() const;
	virtual void setParent(DisplayObject *parent);

	virtual void draw();
	virtual void dispose();

	float getX() const;
	float getY() const;
	float getWorldX() const;
	float getWorldY() const;
	void setX(float x);
	void setY(float y);

	float getScale() const;
	float getScaleX() const;
	float getScaleY() const;
	float getWorldScale() const;
	float getWorldScaleX() const;
	float getWorldScaleY() const;
	void setScale(float scale);
	void setScale(float sx, float sy);
	void setScaleX(float sx);
	void setScaleY(float sy);

	float getRotation() const;
	float getWorldRotation() const;
	float getRotationX() const;
	float getRotationY() const;
	void setRotation(float rotation);
	void setRotation(float rx, float ry);
	void setRotationX(float rx);
	void setRotationY(float ry);

	virtual float getWidth() const;
	virtual void setWidth(float w);
	virtual float getHeight() const;
	virtual void setHeight(float h);

	bool getVisible() const;
	void setVisible(bool visible);

	inline int getUID() const {
		return _uid;
	}

	inline DisplayObjectType getType() const {
		return _type;
	}

protected:
	inline void setType(DisplayObjectType type) {
		_type = type;
	}

protected:
	std::string _name;
	DisplayObject *_parent;
	float _x;
	float _y;
	float _scale, _scaleX, _scaleY;
	float _rotation, _rotationX, _rotationY;
	float _width, _height;
	bool _visible;
	DisplayObjectType _type;

private:
	int _uid;
};
NS_QUICK_DISPLAY_END

#endif