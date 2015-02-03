local cLayer = require "quick.Layer"
local setmetatable = setmetatable

local Package = {}
local layers = {}
local layer_meta = {}

function Package.createLayer()
	local layer = {}
	table.insert(layers, layer)
	
	layer.layerID = cLayer.createLayer()
	
	return layer
end


function layer_meta:addSprite(sprite)
	
end

return Package