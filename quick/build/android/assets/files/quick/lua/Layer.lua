local cLayerPack = require "quick.Layer"
local method = cLayerPack.method
local getCommon = cLayerPack.getCommon
local setCommon = cLayerPack.setCommon
local eventMethod = cLayerPack.eventMethod

local setmetatable = setmetatable

local Events = require "quick.lua.Events"
local ObjectsKeeper = require "quick.lua.ObjectsKeeper"

local Layer = {}
local layerMeta = {}

function layerMeta.__index(tbl, key)
	if layerMeta[key] then
		return layerMeta[key]
	end
	local getterCommon = getCommon[key]
	if getterCommon then
		return getterCommon(tbl.cLayer)
	end
	error("[Layer] Unsupport get method : " .. key)
end

function layerMeta.__newindex(tbl, key, v)
	local setterCommon = setCommon[key]
	if setterCommon then
		setterCommon(tbl.cLayer, v)
		return
	end
	error("[Layer] Unsupport set method : " .. key)
end

function Layer.createLayer()
	local cLayer = cLayerPack.createLayer()
	local layer = {cLayer = cLayer}
	
	ObjectsKeeper.keep(cLayer, layer)

	return setmetatable(layer, layerMeta)
end

---
---getter
--- .x .y .scaleX .scaleY .scale .rotation .visible

---
---setter
--- .x .y .scaleX .scaleY .scale .rotation .visible

---
---methods
--- nothing

---
---下面是显式定义的方法
---
function layerMeta:addSprite(sprite)
	method["addSprite"](self.cLayer, sprite.cSprite)
end

function layerMeta:addSpriteAt(sprite, index)
	method["addSpriteAt"](self.cLayer, sprite.cSprite, index)
end

function layerMeta:removeSprite(sprite)
	method["removeSprite"](self.cLayer, sprite.cSprite)
end

function layerMeta:removeSpriteAt(index)
	method["removeSpriteAt"](self.cLayer, index)
end

function layerMeta:getSpriteAt(index)
	local lud = method["getSpriteAt"](self.cLayer, index)
	if not lud then
		return nil
	end
	return ObjectsKeeper.fetch(lud)
end

function layerMeta:getSpriteByName(spriteName)
	local lud = method["getSpriteByName"](self.cLayer, spriteName)
	if not lud then return nil end
	return ObjectsKeeper.fetch(lud)
end

function layerMeta:getSpriteIndex(sprite)
	return method["getSpriteIndex"](self.cLayer, sprite.cSprite)
end

function layerMeta:setSpriteIndex(sprite, index)
	method["setSpriteIndex"](self.cLayer, sprite.cSprite, index)
end

function layerMeta:swapSprites(sprite1, sprite2)
	method["swapSprites"](self.cLayer, sprite1.cSprite, sprite2.cSprite)
end

function layerMeta:swapSpritesAt(spriteIndex1, spriteIndex2)
	method["swapSpritesAt"](self.cLayer, spriteIndex1, spriteIndex2)
end

---
---events
---
function layerMeta:addEventListener(strType, func)
	if not func then
		error("[error]addEventListener func == nil...")
		return
	end
	local funcKey = Events.wrapFunc(func)
	eventMethod["addEventListener"](self.cLayer, strType, funcKey)
end

function layerMeta:dispatchEvent(strType)
	eventMethod["dispatchEvent"](self.cLayer, strType)
end

function layerMeta:hasEventListener(strType)
	return eventMethod["hasEventListener"](self.cLayer, strType)
end

function layerMeta:getEventListenerCount(strType)
	return eventMethod["getEventListenerCount"](self.cLayer, strType)
end

function layerMeta:removeEventListener(strType, func)
	local funcKey = Events.wrapFunc(func)
	eventMethod["removeEventListener"](self.cLayer, strType, funcKey)
end

function layerMeta:removeEventListeners(strType)
	eventMethod["removeEventListeners"](self.cLayer, strType)
end

function layerMeta:removeAllEventListener()
	eventMethod["removeAllEventListener"](self.cLayer)
end

---
---dispose
---
function layerMeta:dispose()
	ObjectsKeeper.dispose(self.cLayer)
	method["dispose"](self.cLayer)
end

return Layer