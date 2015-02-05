local cStagePack = require "quick.Stage"
local method = cStagePack.method
local get = cStagePack.get
local set = cStagePack.set

local ObjectsKeeper = require "quick.lua.ObjectsKeeper"

local setmetatable = setmetatable

local Stage = {}
local cStage
local stage = {init = false}
local stageMeta = {}

function stageMeta.__index(tbl, key)
	local getter = get[key]
	if getter then
		return getter(tbl.cStage)
	end
	error("[Stage] Unsupport get method : " .. key)
end

function stageMeta.__newindex(tbl, key, v)
	local setter = set[key]
	if setter then
		setter(tbl.cStage, v)
		return
	end
	error("[Stage] Unsupport set method : " .. key)
end

function Stage.getStage()
	if stage.init then 
		return stage
	end
	
	stage.init = true
	stage.cStage = cStagePack.getStage()
	return setmetatable(stage, stageMeta)
end

function stage:addLayer(layer)
	method["addLayer"](self.cStage, layer.cLayer)
end

function stage:addLayerAt(layer, index)
	method["addLayerAt"](self.cStage, layer.cLayer, index)
end

function stage:removeLayer(layer)
	method["removeLayer"](self.cStage, layer.cLayer)
end

function stage:removeLayerAt(layerIndex)
	method["removeLayerAt"](self.cStage, layerIndex)
end

function stage:getLayerAt(layerIndex)
	local lud = method["getLayerAt"](self.cStage, layerIndex)
	if lud == nil then
		return nil
	end
	return ObjectsKeeper.fetchLayer(lud)
end

function stage:getLayerByName(layerName)
	local lud = method["getLayerByName"](self.cStage, layerName)
	if lud == nil then return nil end
	return ObjectsKeeper.fetchLayer(lud)
end

function stage:getLayerIndex(layer)
	return method["getLayerIndex"](self.cStage, layer.cLayer)
end

function stage:setLayerIndex(layer, index)
	method["setLayerIndex"](self.cStage, layer.cLayer, index)
end

function stage:swapLayers(layer1, layer2)
	method["swapLayers"](self.cStage, layer1.cLayer, layer2.cLayer)
end

function stage:swapLayersAt(layerIndex1, layerIndex2)
	method["swapLayersAt"](self.cStage, layerIndex1, layerIndex2)
end

function stage:clearCanvas(color)
	method["clearCanvas"](self.cStage, color)
end

function stage:draw()
	method["draw"](self.cStage)
end

return Stage