#include "UIDisplayObject.h"

namespace ui {
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

	void UIDisplayObject::setScale(float scale) {
		_scale = scale;
	}

	float UIDisplayObject::getRotation() const {
		return _rotation;
	}

	void UIDisplayObject::setRotation(float rotation) {
		_rotation = rotation;
	}
}