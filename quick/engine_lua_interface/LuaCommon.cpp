#include "LuaCommon.h"

#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>

#include "../engine/display/DisplayObject.h"
using namespace quick::display;

#include "LuaUtils.h"

static int lgetX(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	lua_pushinteger(L, obj->getX());
	return 1;
}

static int lgetY(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	lua_pushinteger(L, obj->getY());
	return 1;
}

static int lgetScaleX(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	lua_pushinteger(L, obj->getScaleX());
	return 1;
}

static int lgetScaleY(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	lua_pushinteger(L, obj->getScaleY());
	return 1;
}

static int lgetRotation(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	lua_pushinteger(L, obj->getRotation());
	return 1;
}

static int lsetX(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	float x = luaL_checknumber(L, 2);
	obj->setX(x);
	return 0;
}

static int lsetY(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	float y = luaL_checknumber(L, 2);
	obj->setY(y);
	return 0;
}

static int lsetScaleX(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	float scaleX = luaL_checknumber(L, 2);
	obj->setScaleX(scaleX);
	return 0;
}

static int lsetScaleY(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	float scaleY = luaL_checknumber(L, 2);
	obj->setScaleY(scaleY);
	return 0;
}

static int lsetRotation(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	float rotation = luaL_checknumber(L, 2);
	obj->setRotation(rotation);
	return 0;
}

void luaCommonGetter(lua_State *L) {
	luaL_Reg l[] = {
		{ "x", lgetX },
		{ "y", lgetY },
		{ "scaleX", lgetScaleX },
		{ "scaleY", lgetScaleY },
		{ "rotation", lgetRotation },
		{ NULL, NULL },
	};

	luaL_newlib(L, l);
}

void luaCommonSetter(lua_State *L) {
	luaL_Reg l[] = {
		{ "x", lsetX },
		{ "y", lsetY },
		{ "scaleX", lsetScaleX },
		{ "scaleY", lsetScaleY },
		{ "rotation", lsetRotation },
		{ NULL, NULL },
	};

	luaL_newlib(L, l);
}