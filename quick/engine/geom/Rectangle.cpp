#include "Rectangle.h"

NS_QUICK_GEOM_BEGIN

Rectangle::Rectangle()
:_x(0), _y(0), _width(0), _height(0)
{
	
}

Rectangle::~Rectangle() {
	
}

Rectangle::Rectangle(float x, float y, float w, float h) 
:_x(x), _y(y), _width(w), _height(h)
{
	
}

Rectangle::Rectangle(const Rectangle &value) {
	_x = value._x;
	_y = value._y;
	_width = value._width;
	_height = value._height;
}

Rectangle &
Rectangle::operator=(const Rectangle &value) {
	_x = value._x;
	_y = value._y;
	_width = value._width;
	_height = value._height;

	return *this;
}

float Rectangle::getX() const {
	return _x;
}

float Rectangle::getY() const {
	return _y;
}

void Rectangle::setX(float x) {
	_x = x;
}

void Rectangle::setY(float y) {
	_y = y;
}

float Rectangle::getWidth() const {
	return _width;
}

float Rectangle::getHeight() const {
	return _height;
}

void Rectangle::setWidth(float w) {
	_width = w;
}

void Rectangle::setHeight(float h) {
	_height = h;
}

float Rectangle::getBottom() const {
	return _y + _height;
}

void Rectangle::getBottomRight(Point &outPoint) const {
	outPoint.setX(_x + _width);
	outPoint.setY(_y + _height);
}

float Rectangle::getLeft() const {
	return _x;
}

float Rectangle::getRight() const {
	return _x + _width;
}

void Rectangle::getSize(Point &outPoint) const {
	outPoint.setX(_width);
	outPoint.setY(_height);
}

float Rectangle::getTop() const {
	return _y;
}

void Rectangle::getTopLeft(Point &outPoint) const {
	outPoint.setX(_x);
	outPoint.setY(_y);
}

Rectangle Rectangle::clone() {
	Rectangle rect;

	rect._x = _x;
	rect._y = _y;
	rect._width = _width;
	rect._height = _height;

	return rect;
}

bool Rectangle::contains(float x, float y) const {
	return (x >= _x && x <= _x + _width && y >= _y && y <= _y + _height);
}

bool Rectangle::containsPoint(const Point &point) const {
	return contains(point.getX(), point.getY());
}

bool Rectangle::containsRect(const Rectangle &rect) const {
	Point topLeft, bottomRight;
	rect.getTopLeft(topLeft);
	rect.getBottomRight(bottomRight);
	return containsPoint(topLeft) && containsPoint(bottomRight);
}

bool Rectangle::operator==(const Rectangle &value) const {
	bool ba = _x == value._x;
	bool bb = _y == value._y;
	bool bc = _width == value._width;
	bool bd = _height == value._height;
	return ba && bb && bc && bd;
}

void Rectangle::setEmpty() {
	_x = _y = _width = _height = 0;
}

NS_QUICK_GEOM_END