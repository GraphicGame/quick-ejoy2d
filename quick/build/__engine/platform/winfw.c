#include <stdlib.h>
#include <stdio.h>

#include "opengl.h"
#include "lauxlib.h"

#include "ejoy2dgame.h"
#include "fault.h"
#include "screen.h"
#include "winfw.h"

#include <android/log.h>
#define LOG_TAG "EJOY2D"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

struct WINDOWGAME {
	struct game *game;
	int intouch;
};

static struct WINDOWGAME *G = NULL;

static const char * startscript =
"local path, script, sw, sh, ss = ...\n"
"local fw = require('ejoy2d.framework')\n"
"fw.WorkDir = path..'/'\n"
"fw.ScreenWidth, fw.ScreenHeight, fw.ScreenScale = sw, sh, ss\n"
"assert(script, 'I need a script name')\n"
"script = path..'/'..script\n"
"package.path = './?.lua;./?/init.lua;'\n"
"package.path = package.path..path..'/?.lua;'\n"
"package.path = package.path..path..'/?/init.lua;'\n"
"package.path = package.path..path..'/src/?.lua;'\n"
"local f = loadfile(script)\n"
"f(script)\n";

static struct WINDOWGAME *
create_game() {
	struct WINDOWGAME * g = (struct WINDOWGAME*)malloc(sizeof(*g));
	g->game = ejoy2d_game();
	g->intouch = 0;
	return g;
}

static int
traceback(lua_State *L) {
	const char *msg = lua_tostring(L, 1);
	if (msg) {
		luaL_traceback(L, L, msg, 1);
	} else if (!lua_isnoneornil(L, 1)) {
		if (!luaL_callmeta(L, 1, "__tostring"))
			lua_pushliteral(L, "(no error message)");
	}
	return 1;
}

void
ejoy2d_win_init(int orix, int oriy, int width, int height, float scale, const char* folder) {
	G = create_game();
	lua_State *L = ejoy2d_game_lua(G->game);
	lua_pushcfunction(L, traceback);
	int tb = lua_gettop(L);
	int err = luaL_loadstring(L, startscript);
	if (err) {
		const char *msg = lua_tostring(L,-1);
		LOGE("startscript error=>%s", msg);
		fault("%s", msg);
	}

	lua_pushstring(L, folder);
	//lua_pushstring(L, "src/test_rain_blood.lua");
	lua_pushstring(L, "src/quick.lua");
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);
	lua_pushnumber(L, scale);

	err = lua_pcall(L, 5, 0, tb);
	if (err) {
		const char *msg = lua_tostring(L,-1);
		LOGE("test_rain_blood.lua error=>%s", msg);
		fault("%s", msg);
	}

	lua_pop(L,1);

	screen_init(width,height,scale);
	ejoy2d_game_start(G->game);
}

void
ejoy2d_win_release() {
	ejoy2d_game_exit(G->game);
}

void
ejoy2d_win_update(float dt) {
	ejoy2d_game_update(G->game, dt);
}

void
ejoy2d_win_drawframe() {
	ejoy2d_game_drawframe(G->game);
}

void
ejoy2d_win_resume(){
	ejoy2d_game_resume(G->game);
}

void
ejoy2d_win_touch(int x, int y,int touch) {
	switch (touch) {
	case TOUCH_BEGIN:
		G->intouch = 1;
		break;
	case TOUCH_END:
		G->intouch = 0;
		break;
	case TOUCH_MOVE:
		if (!G->intouch) {
			return;
		}
		break;
	}
	// windows only support one touch id (0)
	int id = 0;
	ejoy2d_game_touch(G->game, id, x,y,touch);
}

void
ejoy2d_win_rotate(int width, int height, float scale, int orient) {
    screen_init(width, height, scale);

    switch (orient) {
        case ORIENT_UP:
            ejoy2d_game_message(G->game, 0, NULL, "UP", 0);
            break;

        case ORIENT_DOWN:
            ejoy2d_game_message(G->game, 0, NULL, "DOWN", 0);
            break;

        case ORIENT_LEFT:
            ejoy2d_game_message(G->game, 0, NULL, "LEFT", 0);
            break;

        case ORIENT_RIGHT:
            ejoy2d_game_message(G->game, 0, NULL, "RIGHT", 0);
            break;

        default:
            break;
    }
}
