local cSpritePack = require "quick.Sprite"
local method = cSpritePack.method 
local get = cSpritePack.get
local set = cSpritePack.set
local getCommon = cSpritePack.getCommon
local setCommon = cSpritePack.setCommon

local ObjectsKeeper = require "quick.lua.ObjectsKeeper"
local SpritePack = require "quick.lua.SpritePack"
local SimplePackage = require "quick.lua.SimplePackage"

local setmetatable = setmetatable

local Sprite = {}
local spriteMeta = {}

function spriteMeta.__index(tbl, key)
	if spriteMeta[key] then
		return spriteMeta[key]
	end
	local getter = get[key]
	if getter then
		return getter(tbl.cSprite)
	end
	local getterCommon = getCommon[key]
	if getterCommon then
		return getterCommon(tbl.cSprite)
	end
	error("[Sprite] Unsupport get method : " .. key)
end

function spriteMeta.__newindex(tbl, key, v)
	local setter = set[key]
	if setter then
		setter(tbl.cSprite, v)
		return
	end
	local setterCommon = setCommon[key]
	if setterCommon then
		setterCommon(tbl.cSprite, v)
		return
	end
	error("[Sprite] Unsupport set method : " .. key)
end

function Sprite.createSprite(packageName, spriteName)
	local pack, id = SpritePack.query(packageName, spriteName)
	local cSprite = cSpritePack.createSprite(pack, id)
	local sprite = { cSprite = cSprite }
	
	ObjectsKeeper.keepSprite(cSprite, sprite)
	
	return setmetatable(sprite, spriteMeta)
end

---
---getter
--- .x .y .scaleX .scaleY .scale .rotation .visible .width .height .pivotX .pivotY
--- .frame .totalFrames .type .color .alpha .additive

---
---setter
--- .x .y .scaleX .scaleY .scale .rotation .visible
--- .frame .color .alpha .additive

---
---methods
--- nothing

---
---下面是显式定义的方法
---
function spriteMeta:addChild(sprite)
	method["addChild"](self.cSprite, sprite.cSprite)
end

function spriteMeta:addChildAt(sprite, index)
	method["addChildAt"](self.cSprite, sprite.cSprite, index)
end

function spriteMeta:removeChild(sprite)
	method["removeChild"](self.cSprite, sprite.cSprite)
end

function spriteMeta:removeChildAt(index)
	method["removeChildAt"](self.cSprite, index)
end

function spriteMeta:getChildAt(index)
	return method["getChildAt"](self.cSprite, index)
end

function spriteMeta:getChildByName(spriteName)
	return method["getChildByName"](self.cSprite, spriteName)
end

function spriteMeta:getChildIndex(sprite)
	return method["getChildIndex"](self.cSprite, sprite.cSprite)
end

function spriteMeta:setChildIndex(sprite, index)
	method["setChildIndex"](self.cSprite, sprite.cSprite, index)
end

function spriteMeta:swapChildren(sprite1, sprite2)
	method["swapChildren"](self.cSprite, sprite1.cSprite, sprite2.cSprite)
end

function spriteMeta:swapChildrenAt(spriteIndex1, spriteIndex2)
	method["swapChildrenAt"](self.cSprite, spriteIndex1, spriteIndex2)
end

function spriteMeta:draw()
	method["draw"](self.cSprite)
end

function spriteMeta:setPivot(px, py)
	method["setPivot"](self.cSprite, px, py)
end

function spriteMeta:nextFrame()
	return method["nextFrame"](self.cSprite)
end

---
---dispose
---
function spriteMeta:dispose()
	ObjectsKeeper.disposeLayer(self.cSprite)
	method["dispose"](self.cSprite)
end

return Sprite