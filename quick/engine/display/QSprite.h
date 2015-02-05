#ifndef __SPRITE
#define __SPRITE

#include "../NameSpace.h"
#include "DisplayObjectContainer.h"
#include "sprite.h"

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

protected:
	struct sprite *_cSpritePointer;
};

NS_QUICK_DISPLAY_END

#endif