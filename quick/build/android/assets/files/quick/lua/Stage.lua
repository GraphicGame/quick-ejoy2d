local cStagePack = require "quick.Stage"
local method = cStagePack.method
local get = cStagePack.get
local set = cStagePack.set
local eventMethod = cStagePack.eventMethod
local Events = require "quick.lua.Events"
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
	
	ObjectsKeeper.keep(stage.cStage, stage)
	
	return setmetatable(stage, stageMeta)
end

---
---getter
--- .frameRate

---
---setter
--- .frameRate

---
---methods
--- nothing

---
---下面是显式定义的方法
---
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
	return ObjectsKeeper.fetch(lud)
end

function stage:getLayerByName(layerName)
	local lud = method["getLayerByName"](self.cStage, layerName)
	if lud == nil then return nil end
	return ObjectsKeeper.fetch(lud)
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

---
---events
---
function stage:addEventListener(strType, func)
	if not func then
		error("[error]addEventListener func == nil...")
		return
	end
	local funcKey = Events.wrapFunc(func)
	eventMethod["addEventListener"](self.cStage, strType, funcKey)
end

function stage:dispatchEvent(strType)
	eventMethod["dispatchEvent"](self.cStage, strType)
end

function stage:hasEventListener(strType)
	return eventMethod["hasEventListener"](self.cStage, strType)
end

function stage:getEventListenerCount(strType)
	return eventMethod["getEventListenerCount"](self.cStage, strType)
end

function stage:removeEventListener(strType, func)
	local funcKey = Events.wrapFunc(func)
	eventMethod["removeEventListener"](self.cStage, strType, funcKey)
end

function stage:removeEventListeners(strType)
	eventMethod["removeEventListeners"](self.cStage, strType)
end

function stage:removeAllEventListener()
	eventMethod["removeAllEventListener"](self.cStage)
end

return Stage