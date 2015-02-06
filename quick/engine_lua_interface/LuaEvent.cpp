#include "LuaEvent.h"

#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>

#include "../engine/display/DisplayObject.h"
using namespace quick::display;
using namespace quick::events;

#include "LuaUtils.h"

static int laddEventListener(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	const char *eventType = luaL_checkstring(L, 2);
	const char *funcKey = luaL_checkstring(L, 3);
	obj->addEventListener(eventType, funcKey);
	return 0;
}

static int ldispatchEvent(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	const char *eventType = luaL_checkstring(L, 2);
	obj->dispatchEvent(eventType);
	return 0;
}

static int lhasEventListener(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	const char *eventType = luaL_checkstring(L, 2);
	bool has = obj->hasEventListener(eventType);
	lua_pushboolean(L, has);
	return 1;
}

static int lgetEventListenerCount(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	const char *eventType = luaL_checkstring(L, 2);
	int count = obj->getEventListenerCount(eventType);
	lua_pushinteger(L, count);
	return 1;
}

static int lremoveEventListener(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	const char *eventType = luaL_checkstring(L, 2);
	const char *funcKey = luaL_checkstring(L, 3);

	return 0;
}

void luaEventMethod(lua_State *L) {
	luaL_Reg l[] = {
		{ "addEventListener", laddEventListener },
		{ "dispatchEvent", ldispatchEvent },
		{ "hasEventListener", lhasEventListener },
		{ "getEventListenerCount", lgetEventListenerCount },
		{ "removeEventListener", lremoveEventListener },
		{ NULL, NULL },
	};

	luaL_newlib(L, l);
}