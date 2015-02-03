
#include "LuaLayer.h"

#include <lua.h>
#include <lauxlib.h>

#include "../engine/display/Layer.h"
#include "../engine/display/GlobalDisplayObjects.h"

using namespace quick::display;

static int lcreateLayer(lua_State *L) {
	Layer *layer = new Layer();
	int uid = layer->getUID();
	lua_pushinteger(L, uid);
	return 1;
}

static int laddSprite(lua_State *L) {
	int sprite = luaL_checkinteger(L, -1);
	Sprite *sp = GlobalDisplayObjects::TgetDisplayObjectByUID<Sprite>(sprite);

	return 0;
}

static int laddSpriteAt(lua_State *L) {
	return 0;
}

static int lremoveSprite(lua_State *L) {
	return 0;
}

static int lremoveSpriteAt(lua_State *L) {
	return 0;
}

static int lgetSpriteAt(lua_State *L) {
	return 0;
}

static int lgetSpriteByName(lua_State *L) {
	return 0;
}

static int lgetSpriteIndex(lua_State *L) {
	return 0;
}

static int lsetSpriteIndex(lua_State *L) {
	return 0;
}

static int lswapSprites(lua_State *L) {
	return 0;
}

static int lswapSpritesAt(lua_State *L) {
	return 0;
}

static void lmethod(lua_State *L) {
	luaL_Reg l[] = {
		{ "addSprite", laddSprite },
		{ "addSpriteAt", laddSpriteAt },
		{ "removeSprite", lremoveSprite },
		{ "removeSpriteAt", lremoveSpriteAt },
		{ "getSpriteAt", lgetSpriteAt },
		{ "getSpriteByName", lgetSpriteByName },
		{ "getSpriteIndex", lgetSpriteIndex },
		{ "setSpriteIndex", lsetSpriteIndex },
		{ "swapSprites", lswapSprites },
		{ "swapSpritesAt", lswapSpritesAt },
		{ NULL, NULL }
	};
	luaL_newlib(L, l);
}

int luaLayer(lua_State *L) {
	luaL_Reg l[] = {
		{ "createLayer", lcreateLayer },
		{ NULL, NULL }
	};

	lmethod(L);
	lua_setfield(L, -2, "method");

	return 1;
}