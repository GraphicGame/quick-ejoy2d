
local ObjectsKeeper = {}

local layers = {}
local sprites = {}

function ObjectsKeeper.keepLayer(lud, layer)
	layers[lud] = layer
end

function ObjectsKeeper.fetchLayer(lud)
	return layers[lud]
end

function ObjectsKeeper.disposeLayer(lud)
	--print("layers[lud]=>" .. type(layers[lud]))
	layers[lud] = nil
	--print("layers[lud]=>" .. type(layers[lud]))
end

function ObjectsKeeper.keepSprite(lud, sprite)
	sprites[lud] = sprite
end

function ObjectsKeeper.fetchSprite(lud)
	return sprites[lud]
end

function ObjectsKeeper.disposeSprite(lud)
	sprites[lud] = nil
end

return ObjectsKeeper