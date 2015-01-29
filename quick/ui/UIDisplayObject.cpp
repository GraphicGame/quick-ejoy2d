#include "UIDisplayObject.h"

NS_UI_BEGIN

UIDisplayObject::UIDisplayObject() {
	_name = "";
	_parent = nullptr;
}

UIDisplayObject::~UIDisplayObject() {

}

const std::string&
UIDisplayObject::getName() const {
	return _name;
}

void UIDisplayObject::setName(std::string name) {
	_name = name;
}

void UIDisplayObject::setName(const char *name) {
	_name = name;
}

const UIDisplayObject *
UIDisplayObject::getParent() const {
	return _parent;
}

void UIDisplayObject::setParent(UIDisplayObject *parent) {
	_parent = parent;
}

void UIDisplayObject::draw() {
		
}

float UIDisplayObject::getX() const {
	return _x;
}

void UIDisplayObject::setX(float x) {
	_x = x;
}

float UIDisplayObject::getY() const {
	return _y;
}

void UIDisplayObject::setY(float y) {
	_y = y;
}

float UIDisplayObject::getScale() const {
	return _scale;
}

float UIDisplayObject::getScaleX() const {
	return _scaleX;
}

float UIDisplayObject::getScaleY() const {
	return _scaleY;
}

void UIDisplayObject::setScale(float scale) {
	_scale = scale;
}

void UIDisplayObject::setScale(float sx, float sy) {
	_scaleX = sx;
	_scaleY = sy;
}

void UIDisplayObject::setScaleX(float sx) {
	_scaleX = sx;
}

void UIDisplayObject::setScaleY(float sy) {
	_scaleY = sy;
}

float UIDisplayObject::getRotation() const {
	return _rotation;
}

float UIDisplayObject::getRotationX() const {
	return _rotationX;
}

float UIDisplayObject::getRotationY() const {
	return _rotationY;
}

void UIDisplayObject::setRotation(float rotation) {
	_rotation = rotation;
}

void UIDisplayObject::setRotation(float rx, float ry) {
	_rotationX = rx;
	_rotationY = ry;
}

void UIDisplayObject::setRotationX(float rx) {
	_rotationX = rx;
}

void UIDisplayObject::setRotationY(float ry) {
	_rotationY = ry;
}

float UIDisplayObject::getWidth() const {
	return _width;
}

void UIDisplayObject::setWidth(float w) {
	_width = w;
}

float UIDisplayObject::getHeight() const {
	return _height;
}

void UIDisplayObject::setHeight(float h) {
	_height = h;
}

bool UIDisplayObject::getVisible() const {
	return _visible;
}

void UIDisplayObject::setVisible(bool visible) {
	_visible = visible;
}

NS_UI_END