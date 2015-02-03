local Stage = require "quick.lua.Stage"
local Layer = require "quick.lua.Layer"

local stage = Stage.getStage()
print("stage id=>" .. stage.stageID)

local layer = Layer.createLayer()
print("layer id=>" .. layer.layerID)

stage:addLayer(layer.layerID)
local layerID = stage:getLayerAt(0);
print("layer at 0 =>" .. layerID)