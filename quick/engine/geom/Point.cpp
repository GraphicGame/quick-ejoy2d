
#include "Point.h"

#include <math.h>

NS_QUICK_GEOM_BEGIN

Point::Point() {
	
}

Point::~Point() {
	
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

NS_QUICK_GEOM_END