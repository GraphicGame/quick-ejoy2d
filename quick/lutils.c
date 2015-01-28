#include "lutils.h"
#include "ejoy2dgame.h"

#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>

static int
lua_setfps(lua_State *L) {
	int fps = (int)luaL_checkinteger(L, 1);
	if (fps < 0) {
		return luaL_error(L, "you shouldn't set fps == 0 !");
	}
	ejoy2d_game_logicframe(fps);
}

int
lua_utils(lua_State *L) {
	luaL_Reg l[] = {
		{ "setFPS", lua_setfps },
		{ NULL, NULL },
	};
	luaL_newlib(L, l);
	return 1;
}