
#include "LuaLayer.h"

#include <lua.h>
#include <lauxlib.h>

#include "../engine/display/Layer.h"
#include "../engine/display/GlobalDisplayObjects.h"

#include "LuaUtils.h"
#include "LuaCommon.h"

using namespace quick::display;

static int lcreateLayer(lua_State *L) {
	Layer *layer = new Layer();
	lua_pushlightuserdata(L, layer);
	return 1;
}

static int laddSprite(lua_State *L) {
	Layer *layer = getLayer(L, 1);
	Sprite *sp = getSprite(L, 2);
	if (!layer || !sp) {
		return luaL_error(L, "[Layer::addSprite] nil or type error.");
	}
	layer->addSprite(sp);
	return 0;
}

static int laddSpriteAt(lua_State *L) {
	Layer *layer = getLayer(L, 1);
	Sprite *sp = getSprite(L, 2);
	int index = luaL_checkinteger(L, 3);

	if (!layer || !sp) {
		return luaL_error(L, "[Layer::addSpriteAt] nil or type error.");
	}
	layer->addSpriteAt(sp, index);
	return 0;
}

static int lremoveSprite(lua_State *L) {
	Layer *layer = getLayer(L, 1);
	Sprite *sp = getSprite(L, 2);
	if (!layer || !sp) {
		return luaL_error(L, "[Layer::removeSprite] nil or type error.");
	}
	layer->removeSprite(sp);
	return 0;
}

static int lremoveSpriteAt(lua_State *L) {
	Layer *layer = getLayer(L, 1);
	int index = luaL_checkinteger(L, 2);
	if (!layer) {
		return luaL_error(L, "[Layer::removeSpriteAt] nil or type error.");
	}
	layer->removeSpriteAt(index);
	return 0;
}

static int lgetSpriteAt(lua_State *L) {
	Layer *layer = getLayer(L, 1);
	int index = luaL_checkinteger(L, 2);

	if (!layer) {
		return luaL_error(L, "[Layer::getSpriteAt] nil or type error.");
	}
	Sprite *sp = layer->getSpriteAt(index);
	if (!sp) {
		lua_pushnil(L);
		return 1;
	}
	lua_pushlightuserdata(L, sp);
	return 1;
}

static int lgetSpriteByName(lua_State *L) {
	Layer *layer = getLayer(L, 1);
	const char *name = luaL_checkstring(L, 2);
	if (!layer) {
		return luaL_error(L, "[Layer::getSpriteByName] nil or type error.");
	}
	Sprite *sp = layer->getSpriteByName(name);
	if (!sp) {
		lua_pushnil(L);
		return 1;
	}
	lua_pushlightuserdata(L, layer);
	return 1;
}

static int lgetSpriteIndex(lua_State *L) {
	Layer *layer = getLayer(L, 1);
	Sprite *sp = getSprite(L, 2);
	if (!layer || !sp) {
		return luaL_error(L, "[Layer::getSpriteIndex] nil or type error.");
	}
	int index = layer->getSpriteIndex(sp);
	lua_pushinteger(L, index);
	return 1;
}

static int lsetSpriteIndex(lua_State *L) {
	Layer *layer = getLayer(L, 1);
	Sprite *sp = getSprite(L, 2);
	int index = luaL_checkinteger(L, 3);

	if (!layer || !sp) {
		return luaL_error(L, "[Layer::setSpriteIndex] nil or type error.");
	}
	layer->setSpriteIndex(sp, index);
	return 0;
}

static int lswapSprites(lua_State *L) {
	Layer *layer = getLayer(L, 1);
	Sprite *sp1 = getSprite(L, 2);
	Sprite *sp2 = getSprite(L, 3);
	if (!layer || !sp1 || !sp2) {
		return luaL_error(L, "[Layer::swapSprites] nil or type error.");
	}
	layer->swapSprites(sp1, sp2);
	return 0;
}

static int lswapSpritesAt(lua_State *L) {
	Layer *layer = getLayer(L, 1);
	int index1 = luaL_checkinteger(L, 2);
	int index2 = luaL_checkinteger(L, 3);
	if (!layer) {
		return luaL_error(L, "[Layer::swapSpritesAt] nil or type error.");
	}
	layer->swapSpritesAt(index1, index2);
	return 0;
}

static int ldispose(lua_State *L) {
	Layer *layer = getLayer(L, 1);
	if (layer == nullptr)
		return 0;
	layer->dispose();
	delete layer;
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
		{ "dispose", ldispose },
		{ NULL, NULL }
	};
	luaL_newlib(L, l);
}

int luaLayer(lua_State *L) {
	luaL_Reg l[] = {
		{ "createLayer", lcreateLayer },
		{ NULL, NULL }
	};
	luaL_newlib(L, l);

	lmethod(L);
	lua_setfield(L, -2, "method");

	luaCommonGetter(L);
	lua_setfield(L, -2, "getCommon");

	luaCommonSetter(L);
	lua_setfield(L, -2, "setCommon");

	return 1;
}