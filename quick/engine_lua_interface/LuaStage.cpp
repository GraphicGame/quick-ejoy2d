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
	lua_pushinteger(L, _Stage->getUID());
	return 1;
}

static int laddLayer(lua_State *L) {
	int layerID = luaL_checkinteger(L, -1);
	Layer *layer = _getLayer(layerID);
	if (!layer) {
		return luaL_error(L, "[addLayer] layer == null or it's not a layer.");
	}
	_Stage->addLayer(layer);

	return 0;
}

static int laddLayerAt(lua_State *L) {
	int layerID = luaL_checkinteger(L, -1);
	int index = luaL_checkinteger(L, -2);
	Layer *layer = _getLayer(layerID);
	if (!layer) {
		return luaL_error(L, "[addLayerAt] layer == null or it's not a layer.");
	}
	_Stage->addLayerAt(layer, index);

	return 0;
}

static int lremoveLayer(lua_State *L) {
	int layerID = luaL_checkinteger(L, -1);
	Layer *layer = _getLayer(layerID);
	if (!layer) {
		return luaL_error(L, "[removeLayer] layer == null or it's not a layer.");
	}
	_Stage->removeLayer(layer);
	
	return 0;
}

static int lremoveLayerAt(lua_State *L) {
	int index = luaL_checkinteger(L, -1);
	_Stage->removeLayerAt(index);

	return 0;
}

static int lgetLayerAt(lua_State *L) {
	int index = luaL_checkinteger(L, -1);
	lua_settop(L, 0);
	Layer *layer = _Stage->getLayerAt(index);
	if (!layer) {
		lua_pushnil(L);
		return 1;
	}
	lua_pushinteger(L, layer->getUID());
	return 1;
}

static int lgetLayerByName(lua_State *L) {
	const char *name = luaL_checkstring(L, -1);
	lua_settop(L, 0);
	DisplayObject *obj = _Stage->getLayerByName(name);
	if (!obj) {
		lua_pushnil(L);
		return 1;
	}
	assert(obj->getType() == LAYER);
	lua_pushinteger(L, obj->getUID());
	return 1;
}

static int lgetLayerIndex(lua_State *L) {
	int layerID = luaL_checkinteger(L, -1);
	lua_settop(L, 0);
	Layer *layer = _getLayer(layerID);
	if (!layer) {
		lua_pushnil(L);
		return 1;
	}
	lua_pushinteger(L, _Stage->getLayerIndex(layer));
	return 1;
}

static int lsetLayerIndex(lua_State *L) {
	int layerID = luaL_checkinteger(L, -1);
	int index = luaL_checkinteger(L, -2);
	lua_settop(L, 0);
	Layer *layer = _getLayer(layerID);
	if (!layer) {
		return luaL_error(L, "[setLayerIndex] layer == null or it's not a layer.");
	}
	_Stage->setLayerIndex(layer, index);

	return 0;
}

static int lswapLayers(lua_State *L) {
	int layerID1 = luaL_checkinteger(L, -1);
	int layerID2 = luaL_checkinteger(L, -2);
	Layer *layer1 = _getLayer(layerID1);
	Layer *layer2 = _getLayer(layerID2);
	if (layer1 == NULL || layer2 == NULL) {
		return luaL_error(L, "[swapLayers] layer == null or it's not a layer");
	}
	_Stage->swapLayers(layer1, layer2);
	return 0;
}

static int lswapLayersAt(lua_State *L) {
	int index1 = luaL_checkinteger(L, -1);
	int index2 = luaL_checkinteger(L, -2);
	assert(index1 > 0 && index2 > 0);
	_Stage->swapLayersAt(index1, index2);
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
	lua_pushinteger(L, _Stage->getFrameRate());
	return 1;
}

static int lsetFrameRate(lua_State *L) {
	int fps = luaL_checkinteger(L, -1);
	_Stage->setFrameRate(fps);
	return 0;
}

static int lgetStageWidth(lua_State *L) {
	lua_pushinteger(L, _Stage->getStageWidth());
	return 1;
}

static int lsetStageWidth(lua_State *L) {
	int w = luaL_checkinteger(L, -1);
	if (w <= 0) {
		return luaL_error(L, "[stageWidth] must > 0");
	}
	_Stage->setStageWidth(w);
	return 0;
}

static int lgetStageHeight(lua_State *L) {
	lua_pushinteger(L, _Stage->getStageHeight());
	return 1;
}

static int lsetStageHeight(lua_State *L) {
	int h = luaL_checkinteger(L, -1);
	if (h <= 0) {
		return luaL_error(L, "[stageHeight] must > 0");
	}
	_Stage->setStageHeight(h);
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