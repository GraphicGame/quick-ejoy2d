#ifndef __SPRITE
#define __SPRITE

#include "../NameSpace.h"
#include "DisplayObjectContainer.h"
#include "sprite.h" 
#include <stdint.h>

NS_QUICK_DISPLAY_BEGIN

class Sprite : public DisplayObjectContainer {
public:
	Sprite();
	virtual ~Sprite();
public:
	void draw() override;
	void dispose() override;
	void setCSpritePointer(struct sprite *s);
	struct sprite * getCSpritePointer() const;

	float getWidth() const override;
	float getHeight() const override;
	void setWidth(float w) override;
	void setHeight(float h) override;

	void setPivotPoint(float px, float py);
	float getPivotPointX() const;
	float getPivotPointY() const;

	int getFrame() const;
	int getTotalFrames() const;

	void setFrame(int frame);

	int getCSpriteType() const;

	uint32_t getColor() const;
	void setColor(uint32_t color);

	uint8_t getAlpha() const;
	void setAlpha(uint8_t alpha);

	uint32_t getAdditive() const;
	void setAdditive(uint32_t additive);

	const char *getActionName() const;
	int setActionName(const char *name);

protected:
	struct sprite *_cSpritePointer;
	float _pivotX, _pivotY;
};

NS_QUICK_DISPLAY_END

#endif