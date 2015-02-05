#include "Layer.h"
#include "DisplayObjectType.h"
#include "Stage.h"
#include "QSprite.h"

#include <assert.h>

NS_QUICK_DISPLAY_BEGIN

Layer::Layer() {
	setType(LAYER);
}

Layer::~Layer() {
	
}

void Layer::draw() {
	for (_itChildrenList it = _childrenList.begin(); it != _childrenList.end(); ++it) {
		DisplayObject *obj = *it;
		assert(obj->getType() == SPRITE);
		if (!obj->getVisible())
			continue;
		Sprite *sprite = static_cast<Sprite*>(obj);
		sprite->draw();
	}
}

void Layer::dispose() {
	//dispose all children.
	for (_itChildrenList it = _childrenList.begin(); it != _childrenList.end(); ++it) {
		DisplayObject *obj = *it;
		assert(obj->getType() == SPRITE);
		Sprite *sprite = static_cast<Sprite*>(obj);
		sprite->dispose();

		//@to do
		//??---delete sprite ??
	}

	//remove myself from the stage.
	Stage::getInstance()->removeLayer(this);
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

Sprite *
Layer::getSpriteAt(int index) {
	DisplayObject *obj = getChildAt(index);
	assert(obj->getType() == SPRITE);
	return static_cast<Sprite*>(obj);
}

Sprite *
Layer::getSpriteByName(std::string name) {
	DisplayObject *obj = getSpriteByName(name);
	assert(obj->getType() == SPRITE);
	return static_cast<Sprite*>(obj);
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