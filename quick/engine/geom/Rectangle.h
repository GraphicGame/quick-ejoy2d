#ifndef __RECTANGLE
#define __RECTANGLE

#include "../NameSpace.h"
#include "Point.h"

NS_QUICK_GEOM_BEGIN

class Rectangle {
public:
	Rectangle();
	~Rectangle();
	Rectangle(const Rectangle &value);
	Rectangle(float x, float y, float w, float h);
public:
	Rectangle& operator=(const Rectangle &value);
	bool operator==(const Rectangle &value) const;
public:
	float getX() const;
	float getY() const;
	void setX(float x);
	void setY(float y);

	float getWidth() const;
	float getHeight() const;
	void setWidth(float w);
	void setHeight(float h);

	float getBottom() const;
	void getBottomRight(Point &outPoint) const;
	float getLeft() const;
	float getRight() const;
	void getSize(Point &outPoint) const;
	float getTop() const;
	void getTopLeft(Point &outPoint) const;

	Rectangle clone();
	bool contains(float x, float y) const;
	bool containsPoint(const Point &point) const;
	bool containsRect(const Rectangle &rect) const;
	void setEmpty();

private:
	float _x, _y;
	float _width, _height;
};

NS_QUICK_GEOM_END

#endif