local cStage = require "quick.Stage"
local method = cStage.method
local get = cStage.get
local set = cStage.set

local setmetatable = setmetatable
local debug = debug

local Stage = {}
local stage
local stage_meta = {}

function stage_meta.__index(t, key)
	if method[key] then
		return method[key]
	end
	local getter = get[key]
	if getter then
		return getter(t.cobj)
	end
	error("[Stage]Unsupport get method : " .. key)
end

function stage_meta.__newindex(t, key, v)
	local setter = set[key]
	if setter then
		setter(t.cobj, v)
		return
	end
	error("[Stage]Unsupport set method : " .. key)
end

function Stage.getStage()
	if stage ~= nil then 
		return stage
	end
	
	--[[stage = { cobj = 0 }
	local cobj = cStage.getStage()
	stage.cobj = cobj;
	return setmetatable(stage, stage_meta)]]
	stage = cStage.getStage()
	return debug.setmetatable(stage, stage_meta)
end

--[[ stage成员函数列表如下:
function stage:addLayer(layer)
end

function stage:addLayerAt(layer)
end

function stage:removeLayer(layer)
end

function stage:removeLayerAt(layerIndex)
end

function stage:getLayerAt(layerIndex)
end

function stage:getLayerByName(layerName)
end

function stage:getLayerIndex(layer)
end

function stage:setLayerIndex(layer)
end

function stage:swapLayers(layer1, layer2)
end

function stage:swapLayersAt(layerIndex1, layerIndex2)
end
]]

return Stage