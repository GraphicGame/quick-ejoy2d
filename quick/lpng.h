#ifndef __IMG_PNG_H__
#define __IMG_PNG_H__

#include <stdint.h>
#include <lua.h>

#define PNG_UNKNOWN 0
#define PNG_RGBA 1
#define PNG_RGB 2

int lua_png(lua_State *L);

#endif
