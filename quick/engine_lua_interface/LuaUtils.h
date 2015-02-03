#include "../engine/display/GlobalDisplayObjects.h"
#include "../engine/display/Layer.h"
#include "../engine/display/QSprite.h"

using namespace quick::display;

static inline Layer * _getLayer(int layerID) {
	return GlobalDisplayObjects::TgetDisplayObjectByUID<Layer>(layerID);
}

static inline Sprite * _getSprite(int spriteID) {
	return GlobalDisplayObjects::TgetDisplayObjectByUID<Sprite>(spriteID);
}