#include "Layer.h"
#include "DisplayObjectType.h"

NS_QUICK_DISPLAY_BEGIN

Layer::Layer() {
	setType(LAYER);
}

Layer::~Layer() {
	
}

void Layer::draw() {
	
}

void Layer::addSprite(Sprite *sprite) {
	addChild(sprite);
}

void Layer::addSpriteAt(Sprite *sprite, int index) {
	addChildAt(sprite, index);
}

void Layer::removeSprite(Sprite *sprite) {
	removeChild(sprite);
}

void Layer::removeSpriteAt(int index) {
	removeChildAt(index);
}

DisplayObject *
Layer::getSpriteAt(int index) {
	return getChildAt(index);
}

DisplayObject *
Layer::getSpriteByName(std::string name) {
	return getSpriteByName(name);
}

int Layer::getSpriteIndex(Sprite *sprite) {
	return getChildIndex(sprite);
}

void Layer::setSpriteIndex(Sprite *sprite, int index) {
	setChildIndex(sprite, index);
}

void Layer::swapSprites(Sprite *sprite1, Sprite *sprite2) {
	swapChildren(sprite1, sprite2);
}

void Layer::swapSpritesAt(int index1, int index2) {
	swapChildrenAt(index1, index2);
}

NS_QUICK_DISPLAY_END