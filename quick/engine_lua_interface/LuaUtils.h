#include "../engine/display/GlobalDisplayObjects.h"
#include "../engine/display/Stage.h"
#include "../engine/display/Layer.h"
#include "../engine/display/QSprite.h"

using namespace quick::display;

#include <lua.h>

#define  getStage(L, index) (Stage*)lua_touserdata(L, index)

#define getLayer(L, index) (Layer*)lua_touserdata(L, index)

#define getSprite(L, index) (Sprite*)lua_touserdata(L, index)
