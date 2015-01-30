
#include "Point.h"

#include <math.h>

NS_QUICK_GEOM_BEGIN

Point::Point()
:_x(0), _y(0)
{
	
}

Point::~Point() {
	
}

Point::Point(float x, float y) 
:_x(x), _y(y)
{
	
}

Point::Point(const Point &value) {
	_x = value._x;
	_y = value._y;
}

Point &
Point::operator=(const Point &value) {
	_x = value._x;
	_y = value._y;

	return *this;
}

float Point::getX() const {
	return _x;
}

float Point::getY() const {
	return _y;
}

void Point::setX(float x) {
	_x = x;
}

void Point::setY(float y) {
	_y = y;
}

float Point::getLength() const {
	return sqrtf(_x * _x + _y * _y);
}

bool Point::operator==(const Point &value) const {
	return (_x == value._x && _y == value._y);
}

NS_QUICK_GEOM_END