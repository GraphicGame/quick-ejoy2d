#include "QSprite.h"
#include "DisplayObjectType.h"
#include <stdlib.h>
#include <assert.h>

#include "matrix.h"
#include "sprite.h"

NS_QUICK_DISPLAY_BEGIN

Sprite::Sprite() 
	:_cSpritePointer(NULL)
{
	setType(SPRITE);
}

Sprite::~Sprite() {
	if (_cSpritePointer != NULL) {
		free(_cSpritePointer);
	}
}

void Sprite::draw() {
	struct srt srt = {
		getWorldX() * 16, getWorldY() * 16,
		getWorldScaleX() * 1024, getWorldScaleY() * 1024,
		getWorldRotation()
	};

	sprite_draw(_cSpritePointer, &srt);

	for (_itChildrenList it = _childrenList.begin();
		it != _childrenList.end(); ++it) {
		DisplayObject *obj = *it;
		assert(obj->getType() == SPRITE);
		if (!obj->getVisible())
			continue;
		Sprite *sprite = static_cast<Sprite*>(obj);
		sprite->draw();
	}
}

void Sprite::dispose() {
	if (_cSpritePointer != NULL) {
		free(_cSpritePointer);
	}
}

void Sprite::setCSpritePointer(struct sprite *s) {
	_cSpritePointer = s;
}

struct sprite * Sprite::getCSpritePointer() const {
	return _cSpritePointer;
}

NS_QUICK_DISPLAY_END