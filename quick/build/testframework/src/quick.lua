local Stage = require "quick.lua.Stage"
local Layer = require "quick.lua.Layer"

local stage = Stage.getStage()
local layer = Layer.createLayer()

stage:addLayer(layer)
local layerIndex = stage:getLayerIndex(layer)

print("layerIndex = " .. layerIndex)