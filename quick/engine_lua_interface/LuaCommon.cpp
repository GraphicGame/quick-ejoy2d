#include "LuaCommon.h"

#include <stdlib.h>

#include "../engine/display/DisplayObject.h"
using namespace quick::display;

#include "LuaUtils.h"
#include "LuaCpp.h"

static int lgetX(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	lua_pushnumber(L, obj->getX());
	return 1;
}

static int lgetY(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	lua_pushnumber(L, obj->getY());
	return 1;
}

static int lgetScaleX(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	lua_pushnumber(L, obj->getScaleX());
	return 1;
}

static int lgetScaleY(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	lua_pushnumber(L, obj->getScaleY());
	return 1;
}

static int lgetScale(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	lua_pushnumber(L, obj->getScale());
	return 1;
}

static int lgetRotation(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	lua_pushinteger(L, obj->getRotation());
	return 1;
}

static int lgetVisible(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	lua_pushboolean(L, obj->getVisible());
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

static int lsetScale(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	float scale = luaL_checknumber(L, 2);
	obj->setScale(scale);
	return 0;
}

static int lsetRotation(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	float rotation = luaL_checknumber(L, 2);
	obj->setRotation(rotation);
	return 0;
}

static int lsetVisible(lua_State *L) {
	DisplayObject *obj = getDisplayObject(L, 1);
	bool v = lua_toboolean(L, 2);
	obj->setVisible(v);
	return 0;
}

void luaCommonGetter(lua_State *L) {
	luaL_Reg l[] = {
		{ "x", lgetX },
		{ "y", lgetY },
		{ "scaleX", lgetScaleX },
		{ "scaleY", lgetScaleY },
		{ "scale", lgetScale },
		{ "rotation", lgetRotation },
		{ "visible", lgetVisible },
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
		{ "scale", lsetScale },
		{ "rotation", lsetRotation },
		{ "visible", lsetVisible },
		{ NULL, NULL },
	};

	luaL_newlib(L, l);
}