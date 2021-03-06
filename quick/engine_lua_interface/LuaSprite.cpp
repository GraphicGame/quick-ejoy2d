#include "LuaSprite.h"

#include <stdlib.h>

#include "../engine/display/QSprite.h"
using namespace quick::display;

#include "LuaUtils.h"
#include "LuaCommon.h"
#include "LuaEvent.h"
#include "LuaCpp.h"

#include "spritepack.h"
#include "sprite.h"
#include "matrix.h"
#include "shader.h"

static void
updateMessage(struct sprite * s, struct sprite_pack * pack, int parentid, int componentid, int frame) {
	struct pack_animation * ani = (struct pack_animation *)pack->data[parentid];
	if (frame < 0 || frame >= ani->frame_number) {
		return;
	}
	struct pack_frame pframe = ani->frame[frame];
	int i = 0;
	for (; i < pframe.n; i++) {
		if (pframe.part[i].component_id == componentid && pframe.part[i].touchable) {
			s->message = true;
			return;
		}
	}
}

static struct sprite *
newAnchor() {
	int sz = sizeof(struct sprite) + sizeof(struct anchor_data);
	struct sprite * s = (struct sprite *)malloc(sz);
	s->parent = NULL;
	s->t.mat = NULL;
	s->t.color = 0xffffffff;
	s->t.additive = 0;
	s->t.program = PROGRAM_DEFAULT;
	s->message = false;
	s->visible = false;	// anchor is invisible by default
	s->multimount = false;
	s->name = NULL;
	s->id = ANCHOR_ID;
	s->type = TYPE_ANCHOR;
	s->data.anchor = (struct anchor_data *)(s + 1);
	s->data.anchor->ps = NULL;
	s->data.anchor->pic = NULL;
	s->s.mat = &s->data.anchor->mat;
	s->material = NULL;
	matrix_identity(s->s.mat);

	return s;
}

static struct sprite *
newSprite(struct sprite_pack *pack, int id) {
	if (id == ANCHOR_ID) {
		return newAnchor();
	}
	int sz = sprite_size(pack, id);
	if (sz == 0) {
		return NULL;
	}
	struct sprite * s = (struct sprite *)malloc(sz);
	sprite_init(s, pack, id, sz);

	for (int i = 0;; i++) {
		int childid = sprite_component(s, i);
		if (childid < 0)
			break;
		struct sprite *c = newSprite(pack, childid);
		if (c) {
			c->name = sprite_childname(s, i);
			sprite_mount(s, i, c);
			updateMessage(c, pack, id, i, s->frame);
		}
	}
	
	return s;
}

static int lcreateSprite(lua_State *L) {
	struct sprite_pack *pack = (struct sprite_pack *)lua_touserdata(L, 1);
	if (pack == NULL) {
		return luaL_error(L, "Sprite::createSprite sprite_pack == NULL");
	}
	int id = luaL_checkinteger(L, 2);
	struct sprite *s = newSprite(pack, id);

	Sprite *sprite = new Sprite();
	sprite->setCSpritePointer(s);
	lua_pushlightuserdata(L, sprite);
	return 1;
}

static int laddChild(lua_State *L) {
	Sprite *parent = getSprite(L, 1);
	Sprite *child = getSprite(L, 2);
	parent->addChild(child);
	return 0;
}

static int laddChildAt(lua_State *L) {
	Sprite *parent = getSprite(L, 1);
	Sprite *child = getSprite(L, 2);
	int index = luaL_checkinteger(L, 3);
	parent->addChildAt(child, index);
	return 0;
}

static int lremoveChild(lua_State *L) {
	Sprite *parent = getSprite(L, 1);
	Sprite *child = getSprite(L, 2);
	parent->removeChild(child);
	return 0;
}

static int lremoveChildAt(lua_State *L) {
	Sprite *parent = getSprite(L, 1);
	int index = luaL_checkinteger(L, 2);
	parent->removeChildAt(index);
	return 0;
}

static int lgetChildAt(lua_State *L) {
	Sprite *parent = getSprite(L, 1);
	int index = luaL_checkinteger(L, 2);
	Sprite *child = (Sprite*)parent->getChildAt(index);
	if (child == nullptr) {
		lua_pushnil(L);
		return 1;
	}
	lua_pushlightuserdata(L, child);
	return 1;
}

static int lgetChildByName(lua_State *L) {
	Sprite *parent = getSprite(L, 1);
	const char *name = luaL_checkstring(L, 2);
	Sprite *child = (Sprite*)parent->getChildByName(name);
	if (child == nullptr) {
		lua_pushnil(L);
		return 1;
	}
	lua_pushlightuserdata(L, child);
	return 1;
}

static int lgetChildIndex(lua_State *L) {
	Sprite *parent = getSprite(L, 1);
	Sprite *child = getSprite(L, 2);
	int index = parent->getChildIndex(child);
	lua_pushinteger(L, index);
	return 1;
}

static int lswapChildren(lua_State *L) {
	Sprite *parent = getSprite(L, 1);
	Sprite *child1 = getSprite(L, 2);
	Sprite *child2 = getSprite(L, 3);
	parent->swapChildren(child1, child2);
	return 0;
}

static int lswapChildrenAt(lua_State *L) {
	Sprite *parent = getSprite(L, 1);
	int index1 = luaL_checkinteger(L, 2);
	int index2 = luaL_checkinteger(L, 3);
	parent->swapChildrenAt(index1, index2);
	return 0;
}

static int lcontains(lua_State *L) {
	Sprite *parent = getSprite(L, 1);
	Sprite *target = getSprite(L, 2);
	bool contains = parent->contains(target);
	lua_pushboolean(L, contains);
	return 1;
}

//static int ldraw(lua_State *L) {
//	Sprite *parent = getSprite(L, 1);
//	struct sprite *s = parent->getCSpritePointer();
//	struct srt srt {
//		parent->getX() * 16, parent->getY() * 16, 
//		parent->getScaleX() * 1024, parent->getScaleY() * 1024,
//		parent->getRotation()
//	};
//
//	sprite_draw(s, &srt);
//	return 0;
//}

static int lsetPivot(lua_State *L) {
	Sprite *sprite = getSprite(L, 1);
	float px = luaL_checknumber(L, 2);
	float py = luaL_checknumber(L, 3);
	sprite->setPivotPoint(px, py);
	return 0;
}

static int lnextFrame(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	int frame = sp->getFrame();
	sp->setFrame(frame + 1);
	int totalFrames = sp->getTotalFrames();
	lua_pushinteger(L, (frame + 1) % totalFrames);
	return 1;
}

static void lmethod(lua_State *L) {
	luaL_Reg l[] = {
		{ "addChild", laddChild },
		{ "addChildAt", laddChildAt },
		{ "removeChild", lremoveChild },
		{ "removeChildAt", lremoveChildAt },
		{ "getChildAt", lgetChildAt },
		{ "getChildByName", lgetChildByName },
		{ "getChildIndex", lgetChildIndex },
		{ "swapChildren", lswapChildren },
		{ "swapChildrenAt", lswapChildrenAt },
		{ "contains", lcontains },
		//{ "draw", ldraw },
		{ "setPivot", lsetPivot },
		{ "nextFrame", lnextFrame },
		{ NULL, NULL }
	};
	luaL_newlib(L, l);
}

static int lnumChildren(lua_State *L) {
	Sprite *parent = getSprite(L, 1);
	int numChildren = parent->getChildrenCount();
	lua_pushinteger(L, numChildren);
	return 1;
}

static int lgetWidth(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	float spWidth = sp->getWidth();
	lua_pushnumber(L, spWidth);
	return 1;
}

static int lgetHeight(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	float spHeight = sp->getHeight();
	lua_pushnumber(L, spHeight);
	return 1;
}

static int lgetPivotX(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	float px = sp->getPivotPointX();
	lua_pushnumber(L, px);
	return 1;
}

static int lgetPivotY(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	float py = sp->getPivotPointY();
	lua_pushnumber(L, py);
	return 1;
}

static int lgetFrame(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	int frame = sp->getFrame();
	lua_pushinteger(L, frame);
	return 1;
}

static int lgetTotalFrames(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	int totalFrames = sp->getTotalFrames();
	lua_pushinteger(L, totalFrames);
	return 1;
}

static int lgetType(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	int type = sp->getCSpriteType();
	lua_pushinteger(L, type);
	return 1;
}

static int lgetColor(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	uint32_t color = sp->getColor();
	lua_pushunsigned(L, color);
	return 1;
}

static int lgetAlpha(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	uint8_t alpha = sp->getAlpha();
	lua_pushunsigned(L, alpha);
	return 1;
}

static int lgetAdditive(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	uint32_t additive = sp->getAdditive();
	lua_pushunsigned(L, additive);
	return 1;
}

static int lgetActionName(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	const char *name = sp->getActionName();
	lua_pushstring(L, name);
	return 1;
}

static void lgetter(lua_State *L) {
	luaL_Reg l[] = {
		{ "numChildren", lnumChildren },
		{ "width", lgetWidth },
		{ "height", lgetHeight },
		{ "pivotX", lgetPivotX },
		{ "pivotY", lgetPivotY },
		{ "frame", lgetFrame },
		{ "totalFrames", lgetTotalFrames },
		{ "type", lgetType },
		{ "color", lgetColor },
		{ "alpha", lgetAlpha },
		{ "additive", lgetAdditive },
		{ "actionName", lgetActionName },
		{ NULL, NULL },
	};
	luaL_newlib(L, l);
}

static int lsetFrame(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	int frame = luaL_checkinteger(L, 2);
	sp->setFrame(frame);
	return 0;
}

static int lsetColor(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	uint32_t color = luaL_checkunsigned(L, 2);
	sp->setColor(color);
	return 0;
}

static int lsetAlpha(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	uint8_t alpha = luaL_checkunsigned(L, 2);
	sp->setAlpha(alpha);
	return 0;
}

static int lsetAdditive(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	uint32_t additive = luaL_checkunsigned(L, 2);
	sp->setAdditive(additive);
	return 0;
}

static int lsetActionName(lua_State *L) {
	Sprite *sp = getSprite(L, 1);
	const char *name = luaL_checkstring(L, 2);
	int totalFrames = sp->setActionName(name);
	//lua_pushboolean(L, totalFrames != 0);
	return 0;
}

static void lsetter(lua_State *L) {
	luaL_Reg l[] = {
		{ "frame", lsetFrame },
		{ "color", lsetColor },
		{ "alpha", lsetAlpha },
		{ "additive", lsetAdditive },
		{ "actionName", lsetActionName },
		{ NULL, NULL },
	};
	luaL_newlib(L, l);
}

int luaSprite(lua_State *L) {
	luaL_Reg l[] = {
		{ "createSprite", lcreateSprite },
		{ NULL, NULL },
	};
	luaL_newlib(L, l);

	lmethod(L);
	lua_setfield(L, -2, "method");

	lgetter(L);
	lua_setfield(L, -2, "get");

	lsetter(L);
	lua_setfield(L, -2, "set");

	luaCommonGetter(L);
	lua_setfield(L, -2, "getCommon");

	luaCommonSetter(L);
	lua_setfield(L, -2, "setCommon");

	luaEventMethod(L);
	lua_setfield(L, -2, "eventMethod");

	return 1;
}