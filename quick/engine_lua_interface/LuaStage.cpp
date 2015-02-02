#include "LuaStage.h"

#include <lua.h>
#include <lauxlib.h>

#include <assert.h>

#include "../engine/display/Stage.h"
#include "../engine/display/Layer.h"
#include "../engine/display/GlobalDisplayObjects.h"
using namespace quick::display;

Stage *_Stage = nullptr;

static int lgetStage(lua_State *L) {
	if (!_Stage) {
		_Stage = new Stage();
	}
	return 0;
}

static int laddLayer(lua_State *L) {
	int layerID = luaL_checkinteger(L, -1);
	DisplayObject *obj = GlobalDisplayObjects::getDisplayObjectByUID(layerID);
	if (obj->getType() != LAYER) {
		return luaL_error(L, "[addLayer]Stage can only add Layer as it's child !");
	}
	_Stage->addLayer((Layer*)obj);

	return 0;
}

static int laddLayerAt(lua_State *L) {
	int layerID = luaL_checkinteger(L, -1);
	int index = luaL_checkinteger(L, -2);
	DisplayObject *obj = GlobalDisplayObjects::getDisplayObjectByUID(layerID);
	if (obj->getType() != LAYER) {
		return luaL_error(L, "[addLayerAt]Stage can only add Layer as it's child !");
	}
	_Stage->addLayerAt((Layer*)obj, index);

	return 0;
}

static int lremoveLayer(lua_State *L) {
	int layerID = luaL_checkinteger(L, -1);
	DisplayObject *obj = GlobalDisplayObjects::getDisplayObjectByUID(layerID);
	if (obj->getType() != LAYER) {
		return luaL_error(L, "[removeLayer] param type error...")
	}
	_Stage->removeLayer((Layer*)obj);
	
	return 0;
}

static int lremoveLayerAt(lua_State *L) {
	int layerID = luaL_checkinteger(L, -1);
	int index = luaL_checkinteger(L, -2);
	DisplayObject *obj = GlobalDisplayObjects::getDisplayObjectByUID(layerID);
	if (obj->getType() != LAYER) {
		return luaL_error(L, "[removeLayer] param type error...")
	}
	_Stage->removeLayerAt(obj, index);

	return 0;
}

static int lgetLayerAt(lua_State *L) {
	int index = luaL_checkinteger(L, -1);
	DisplayObject *obj = _Stage->getLayerAt(index);
	assert(obj->getType() == LAYER);

}

static void lmethod(lua_State *L) {
	luaL_Reg l[] = {
		{ "addLayer", laddLayer },
		{ "addLayerAt", laddLayerAt },
		{ "removeLayer", lremoveLayer },
		{ "removeLayerAt", lremoveLayerAt },
		{ "getLayerAt", lgetLayerAt },
		{ NULL, NULL }
	};
	luaL_newlib(L, l);
}

static void lgetter(lua_State *L) {
	
}

static void lsetter(lua_State *L) {
		
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