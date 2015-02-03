#include "LuaStage.h"

#include <lua.h>
#include <lauxlib.h>

#include <assert.h>

#include "../engine/display/Stage.h"
#include "../engine/display/Layer.h"
#include "../engine/display/GlobalDisplayObjects.h"

#include "LuaUtils.h"

using namespace quick::display;

Stage *_Stage = nullptr;

static int lgetStage(lua_State *L) {
	if (!_Stage) {
		_Stage = new Stage();
	}
	lua_pushlightuserdata(L, _Stage);
	return 1;
}

static int laddLayer(lua_State *L) {
	Stage *stage = getStage(L, 1);
	Layer *layer = getLayer(L, 2);
	if (!layer) {
		return luaL_error(L, "[Stage::addLayer] layer == null or it's not a layer.");
	}
	stage->addLayer(layer);

	return 0;
}

static int laddLayerAt(lua_State *L) {
	Stage *stage = getStage(L, 1);
	Layer *layer = getLayer(L, 2);
	int index = luaL_checkinteger(L, 3);
	if (!layer) {
		return luaL_error(L, "[Stage::addLayerAt] layer == null or it's not a layer.");
	}
	stage->addLayerAt(layer, index);

	return 0;
}

static int lremoveLayer(lua_State *L) {
	Stage *stage = getStage(L, 1);
	Layer *layer = getLayer(L, 2);
	if (!layer) {
		return luaL_error(L, "[Stage::removeLayer] layer == null or it's not a layer.");
	}
	stage->removeLayer(layer);
	
	return 0;
}

static int lremoveLayerAt(lua_State *L) {
	Stage *stage = getStage(L, 1);
	int index = luaL_checkinteger(L, 2);
	stage->removeLayerAt(index);

	return 0;
}

static int lgetLayerAt(lua_State *L) {
	Stage *stage = getStage(L, 1);
	int index = luaL_checkinteger(L, 2);
	Layer *layer = stage->getLayerAt(index);
	if (!layer) {
		lua_pushnil(L);
		return 1;
	}
	lua_pushlightuserdata(L, layer);
	return 1;
}

static int lgetLayerByName(lua_State *L) {
	Stage *stage = getStage(L, 1);
	const char *name = luaL_checkstring(L, 2);
	lua_settop(L, 0);
	Layer *layer = stage->getLayerByName(name);
	if (!layer) {
		lua_pushnil(L);
		return 1;
	}
	lua_pushlightuserdata(L, layer);
	return 1;
}

static int lgetLayerIndex(lua_State *L) {
	Stage *stage = getStage(L, 1);
	Layer *layer = getLayer(L, 2);
	lua_settop(L, 0);
	if (!layer) {
		lua_pushnil(L);
		return 1;
	}
	lua_pushinteger(L, stage->getLayerIndex(layer));
	return 1;
}

static int lsetLayerIndex(lua_State *L) {
	Stage *stage = getStage(L, 1);
	Layer *layer = getLayer(L, 2);
	int index = luaL_checkinteger(L, 3);
	lua_settop(L, 0);
	if (!layer) {
		return luaL_error(L, "[Stage::setLayerIndex] layer == null or it's not a layer.");
	}
	stage->setLayerIndex(layer, index);

	return 0;
}

static int lswapLayers(lua_State *L) {
	Stage *stage = getStage(L, 1);
	Layer *layer1 = getLayer(L, 2);
	Layer *layer2 = getLayer(L, 3);
	if (layer1 == NULL || layer2 == NULL) {
		return luaL_error(L, "[Stage::swapLayers] layer == null or it's not a layer");
	}
	stage->swapLayers(layer1, layer2);
	return 0;
}

static int lswapLayersAt(lua_State *L) {
	Stage *stage = getStage(L, 1);
	int index1 = luaL_checkinteger(L, 2);
	int index2 = luaL_checkinteger(L, 3);
	assert(index1 > 0 && index2 > 0);
	stage->swapLayersAt(index1, index2);
	return 0;
}

static void lmethod(lua_State *L) {
	luaL_Reg l[] = {
		{ "addLayer", laddLayer },
		{ "addLayerAt", laddLayerAt },
		{ "removeLayer", lremoveLayer },
		{ "removeLayerAt", lremoveLayerAt },
		{ "getLayerAt", lgetLayerAt },
		{ "getLayerByName", lgetLayerByName },
		{ "getLayerIndex", lgetLayerIndex },
		{ "setLayerIndex", lsetLayerIndex },
		{ "swapLayers", lswapLayers },
		{ "swapLayersAt", lswapLayersAt },
		{ NULL, NULL }
	};
	luaL_newlib(L, l);
}

static int lgetFrameRate(lua_State *L) {
	Stage *stage = getStage(L, 1);
	lua_pushinteger(L, stage->getFrameRate());
	return 1;
}

static int lsetFrameRate(lua_State *L) {
	Stage *stage = getStage(L, 1);
	int fps = luaL_checkinteger(L, 2);
	stage->setFrameRate(fps);
	return 0;
}

static int lgetStageWidth(lua_State *L) {
	Stage *stage = getStage(L, 1);
	lua_pushinteger(L, stage->getStageWidth());
	return 1;
}

static int lsetStageWidth(lua_State *L) {
	Stage *stage = getStage(L, 1);
	int w = luaL_checkinteger(L, 2);
	if (w <= 0) {
		return luaL_error(L, "[Stage::stageWidth] must > 0");
	}
	stage->setStageWidth(w);
	return 0;
}

static int lgetStageHeight(lua_State *L) {
	Stage *stage = getStage(L, 1);
	lua_pushinteger(L, stage->getStageHeight());
	return 1;
}

static int lsetStageHeight(lua_State *L) {
	Stage *stage = getStage(L, 1);
	int h = luaL_checkinteger(L, 2);
	if (h <= 0) {
		return luaL_error(L, "[Stage::stageHeight] must > 0");
	}
	stage->setStageHeight(h);
	return 0;
}

static void lgetter(lua_State *L) {
	luaL_Reg l[] = {
		{ "frameRate", lgetFrameRate },
		{ "stageWidth", lgetStageWidth },
		{ "stageHeight", lgetStageHeight },
		{ NULL, NULL }
	};
	luaL_newlib(L, l);
}

static void lsetter(lua_State *L) {
	luaL_Reg l[] = {
		{ "frameRate", lsetFrameRate },
		{ "stageWidth", lsetStageWidth },
		{ "stageHeight", lsetStageHeight },
		{ NULL, NULL }
	};
	luaL_newlib(L, l);
}

int luaStage(lua_State *L) {
	luaL_Reg l[] = {
		{ "getStage", lgetStage },
		{ NULL, NULL },
	};
	luaL_newlib(L, l);

	lmethod(L);
	lua_setfield(L, -2, "method");
	lgetter(L);
	lua_setfield(L, -2, "get");
	lsetter(L);
	lua_setfield(L, -2, "set");

	return 1;
}