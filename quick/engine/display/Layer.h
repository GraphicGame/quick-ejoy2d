#ifndef __LAYER
#define __LAYER

#include "../NameSpace.h"
#include "DisplayObjectContainer.h"
#include "QSprite.h"

NS_QUICK_DISPLAY_BEGIN

class Layer : public DisplayObjectContainer {
public:
	Layer();
	~Layer();
public:
	void draw() override;
	void dispose() override;

	void addSprite(Sprite *sprite);
	void addSpriteAt(Sprite *sprite, int index);
	void removeSprite(Sprite *sprite);
	void removeSpriteAt(int index);
	Sprite * getSpriteAt(int index);
	Sprite * getSpriteByName(std::string name);
	int getSpriteIndex(Sprite *sprite);
	void setSpriteIndex(Sprite *sprite, int index);
	void swapSprites(Sprite *sprite1, Sprite *sprite2);
	void swapSpritesAt(int index1, int index2);
};

NS_QUICK_DISPLAY_END

#endif