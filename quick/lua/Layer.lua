local cLayerPack = require "quick.Layer"
local method = cLayerPack.method
local getCommon = cLayerPack.getCommon
local setCommon = cLayerPack.setCommon

local setmetatable = setmetatable

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
	
	ObjectsKeeper.keepLayer(cLayer, layer)

	return setmetatable(layer, layerMeta)
end

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
	return method["getSpriteAt"](self.cLayer, index)
end

function layerMeta:getSpriteByName(spriteName)
	return method["getSpriteByName"](self.cLayer, spriteName)
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
---dispose
---
function layerMeta:dispose()
	ObjectsKeeper.disposeLayer(self.cLayer)
	method["dispose"](self.cLayer)
end

return Layer