#include "QSprite.h"
#include "DisplayObjectType.h"
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

#include "matrix.h"
#include "spritepack.h"
#include "sprite.h"
#include "label.h"

NS_QUICK_DISPLAY_BEGIN

#define SRT getWorldX() * 16.0f, getWorldY() * 16.0f,	 \
			getWorldScaleX() * 1024.0f, getWorldScaleY() * 1024.0f, \
			getWorldRotation()

Sprite::Sprite() 
:_cSpritePointer(NULL), _pivotX(0), _pivotY(0)
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
		SRT
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

float Sprite::getWidth() const {
	int32_t *screenCoord;
	struct srt srt {
		SRT
	};
	int aabb[4];
	int cSpriteType = _cSpritePointer->type;

	switch (cSpriteType) {
	case TYPE_PICTURE:
		screenCoord = _cSpritePointer->s.pic->rect[0].screen_coord;
		return (float)((screenCoord[4] / 16 - screenCoord[0] / 16));
	case TYPE_ANIMATION:
	case TYPE_POLYGON:
	case TYPE_LABEL:
	case TYPE_PANNEL:
		sprite_aabb(_cSpritePointer, &srt, true, aabb);
		return (float)(aabb[2] - aabb[0]);
	default:
		break;
	}
	assert(false);
	return 0;
}

float Sprite::getHeight() const {
	int32_t *screenCoord;
	struct srt srt {
		SRT
	};
	int aabb[4];
	int cSpriteType = _cSpritePointer->type;

	switch (cSpriteType) {
	case TYPE_PICTURE:
		screenCoord = _cSpritePointer->s.pic->rect[0].screen_coord;
		return (float)((screenCoord[5] - screenCoord[1]) / SCREEN_SCALE);
	case TYPE_ANIMATION:
	case TYPE_POLYGON:
	case TYPE_LABEL:
	case TYPE_PANNEL:
		sprite_aabb(_cSpritePointer, &srt, true, aabb);
		return (float)(aabb[3] - aabb[1]);
	default:
		break;
	}
	assert(false);
	return 0;
}

void Sprite::setWidth(float w) {
	assert(false);
}

void Sprite::setHeight(float h) {
	assert(false);
}

void Sprite::setPivotPoint(float px, float py) {
	int32_t *screenCoord;
	int cSpriteType = _cSpritePointer->type;
	float picW, picH;
	switch (cSpriteType) {
	case TYPE_PICTURE:
		picW = getWidth();
		picH = getHeight();
		screenCoord = _cSpritePointer->s.pic->rect[0].screen_coord;
		screenCoord[0] = -px;
		screenCoord[1] = -py;
		screenCoord[2] = screenCoord[0];
		screenCoord[3] = picH + screenCoord[1];
		screenCoord[4] = picW + screenCoord[0];
		screenCoord[5] = screenCoord[3];
		screenCoord[6] = screenCoord[4];
		screenCoord[7] = screenCoord[1];

		for (int i = 0; i < 8; i++) {
			screenCoord[i] *= SCREEN_SCALE;
		}
		_pivotX = px;
		_pivotY = py;
		break;
	case TYPE_ANIMATION:
	case TYPE_POLYGON:
	case TYPE_LABEL:
	case TYPE_PANNEL:
		assert(false); //@to do...
		break;
	default:
		break;
	}
}

float Sprite::getPivotPointX() const {
	return _pivotX;
}

float Sprite::getPivotPointY() const {
	return _pivotY;
}

int Sprite::getFrame() const {
	int type = _cSpritePointer->type;
	if (type != TYPE_ANIMATION) {
		return -1;
	}
	return _cSpritePointer->frame;
}

int Sprite::getTotalFrames() const {
	int type = _cSpritePointer->type;
	if (type != TYPE_ANIMATION) {
		return -1;
	}
	return _cSpritePointer->total_frame;
}

void Sprite::setFrame(int frame) {
	int type = _cSpritePointer->type;
	if (type != TYPE_ANIMATION) {
		return;
	}
	_cSpritePointer->frame = frame;
}

int Sprite::getCSpriteType() const {
	return _cSpritePointer->type;
}

uint32_t Sprite::getColor() const {
	int type = _cSpritePointer->type;
	if (type != TYPE_LABEL)
		return _cSpritePointer->t.color;
	else
		return label_get_color(_cSpritePointer->s.label, &_cSpritePointer->t);
}

void Sprite::setColor(uint32_t color) {
	_cSpritePointer->t.color = color;
}

uint8_t Sprite::getAlpha() const {
	return _cSpritePointer->t.color >> 24;
}

void Sprite::setAlpha(uint8_t alpha) {
	_cSpritePointer->t.color = (_cSpritePointer->t.color >> 8) | (alpha << 24);
}

uint32_t Sprite::getAdditive() const {
	return _cSpritePointer->t.additive;
}

void Sprite::setAdditive(uint32_t additive) {
	_cSpritePointer->t.additive = additive;
}

NS_QUICK_DISPLAY_END