local cSprite = require "quick.Stage"
local method = cSprite.method
local get = cSprite.get
local set = cSprite.set

local setmetatable = setmetatable

local Package = {}
local stage = { stageID = -1 }
local stage_meta = {}
setmetatable(stage, stage_meta)

function stage_meta.__index(t, key)
	if method[key] then
		return method[key]
	end
	local getter = get[key]
	if getter then
		return getter()
	end
	error("[Stage]Unsupport get method : " .. key)
end

function stage_meta.__newindex(t, key, v)
	local setter = set[key]
	if setter then
		setter(v)
		return
	end
	error("[Stage]Unsupport set method : " .. key)
end

function Package.getStage()
	stage.stageID = cSprite.getStage()
	return stage
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

return Package