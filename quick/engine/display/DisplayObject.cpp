#include "DisplayObject.h"
#include "../utils/GlobalUIDs.h"
#include "GlobalDisplayObjects.h"

#include <assert.h>

NS_QUICK_DISPLAY_BEGIN

///==== public...
DisplayObject::DisplayObject() 
:_x(0), _y(0), _scale(1), _scaleX(1), _scaleY(1),
_rotation(0), _rotationX(0), _rotationY(0), _width(0), _height(0),
_visible(true)
{
	_name = "";
	_parent = nullptr;

	_uid = GlobalUIDs::getUID();
	GlobalDisplayObjects::add(this);
}

DisplayObject::~DisplayObject() {
	GlobalDisplayObjects::remove(this);
	delete _parent;
	_name.clear();
	_name.swap(std::string());
}

const std::string
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
	assert(false && "should be override");
}

void DisplayObject::dispose() {
	assert(false && "should be override");
}

float DisplayObject::getX() const {
	return _x;
}

float DisplayObject::getWorldX() const {
	const DisplayObject *parent = getParent();
	if (!parent)
		return _x;
	return _x + parent->getWorldX();
}

void DisplayObject::setX(float x) {
	_x = x;
}

float DisplayObject::getY() const {
	return _y;
}

float DisplayObject::getWorldY() const {
	const DisplayObject *parent = getParent();
	if (!parent)
		return _y;
	return _y + parent->getWorldY();
}

void DisplayObject::setY(float y) {
	_y = y;
}

float DisplayObject::getScale() const {
	return _scale;
}

float DisplayObject::getWorldScale() const {
	const DisplayObject *parent = getParent();
	if (!parent)
		return  _scale;
	return _scale * parent->getWorldScale();
}

float DisplayObject::getScaleX() const {
	return _scaleX;
}

float DisplayObject::getWorldScaleX() const {
	const DisplayObject *parent = getParent();
	if (!parent)
		return _scaleX;
	return _scaleX * parent->getWorldScaleX();
}

float DisplayObject::getScaleY() const {
	return _scaleY;
}

float DisplayObject::getWorldScaleY() const {
	const DisplayObject *parent = getParent();
	if (!parent)
		return _scaleY;
	return _scaleY * parent->getWorldScaleY();
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

float DisplayObject::getWorldRotation() const {
	const DisplayObject *parent = getParent();
	if (!parent)
		return _rotation;
	return _rotation + parent->getWorldRotation();
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

///==== protected...

NS_QUICK_DISPLAY_END