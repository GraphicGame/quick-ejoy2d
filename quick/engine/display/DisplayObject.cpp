#include "DisplayObject.h"

NS_QUICK_DISPLAY_BEGIN

DisplayObject::DisplayObject() {
	_name = "";
	_parent = nullptr;
}

DisplayObject::~DisplayObject() {

}

const std::string&
DisplayObject::getName() const {
	return _name;
}

void DisplayObject::setName(std::string name) {
	_name = name;
}

void DisplayObject::setName(const char *name) {
	_name = name;
}

const DisplayObject *
DisplayObject::getParent() const {
	return _parent;
}

void DisplayObject::setParent(DisplayObject *parent) {
	_parent = parent;
}

void DisplayObject::draw() {
		
}

float DisplayObject::getX() const {
	return _x;
}

void DisplayObject::setX(float x) {
	_x = x;
}

float DisplayObject::getY() const {
	return _y;
}

void DisplayObject::setY(float y) {
	_y = y;
}

float DisplayObject::getScale() const {
	return _scale;
}

float DisplayObject::getScaleX() const {
	return _scaleX;
}

float DisplayObject::getScaleY() const {
	return _scaleY;
}

void DisplayObject::setScale(float scale) {
	_scale = scale;
}

void DisplayObject::setScale(float sx, float sy) {
	_scaleX = sx;
	_scaleY = sy;
}

void DisplayObject::setScaleX(float sx) {
	_scaleX = sx;
}

void DisplayObject::setScaleY(float sy) {
	_scaleY = sy;
}

float DisplayObject::getRotation() const {
	return _rotation;
}

float DisplayObject::getRotationX() const {
	return _rotationX;
}

float DisplayObject::getRotationY() const {
	return _rotationY;
}

void DisplayObject::setRotation(float rotation) {
	_rotation = rotation;
}

void DisplayObject::setRotation(float rx, float ry) {
	_rotationX = rx;
	_rotationY = ry;
}

void DisplayObject::setRotationX(float rx) {
	_rotationX = rx;
}

void DisplayObject::setRotationY(float ry) {
	_rotationY = ry;
}

float DisplayObject::getWidth() const {
	return _width;
}

void DisplayObject::setWidth(float w) {
	_width = w;
}

float DisplayObject::getHeight() const {
	return _height;
}

void DisplayObject::setHeight(float h) {
	_height = h;
}

bool DisplayObject::getVisible() const {
	return _visible;
}

void DisplayObject::setVisible(bool visible) {
	_visible = visible;
}

NS_QUICK_DISPLAY_END