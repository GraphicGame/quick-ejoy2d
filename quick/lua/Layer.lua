local cLayer = require "quick.Layer"
local method = cLayer.method

local setmetatable = setmetatable
local debug = debug

local Layer = {}
local layer_meta = {}

function layer_meta.__index(t, key)
	if method[key] then
		return method[key]
	end
	error("[Layer]Unsupport get method : " .. key)
end

function layer_meta.__newindex(t, key, v)
	error("[Layer]Unsupport set method : " .. key)
end

function Layer.createLayer()
	--[[local layer = { cobj = 0 }
	local cobj = cLayer.createLayer()
	layer.cobj = cobj
	return setmetatable(layer, layer_meta)]]
	local layer = cLayer.createLayer()
	--return --[[debug.]]setmetatable(layer, layer_meta)
	return layer
end

return Layer