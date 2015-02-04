#include "QSprite.h"
#include "DisplayObjectType.h"
#include <stdlib.h>

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

void Sprite::dispose() {
	//@to do
}

void Sprite::setCSpritePointer(struct sprite *s) {
	_cSpritePointer = s;
}

struct sprite * Sprite::getCSpritePointer() const {
	return _cSpritePointer;
}

NS_QUICK_DISPLAY_END