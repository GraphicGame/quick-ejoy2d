local Stage = require "quick.lua.Stage"
local Layer = require "quick.lua.Layer"
local Sprite = require "quick.lua.Sprite"
local SimplePackage = require "quick.lua.SimplePackage"
local ej = require "ejoy2d"
local fw = require "ejoy2d.framework"

---
---注意：这个文件只是在测试引擎的功能，因此代码看起来有点乱糟糟的，会经常的改来改去。
---

SimplePackage.load {
	pattern = fw.WorkDir.."quick/build/rainblood/res/?",
	--pattern = fw.WorkDir.."res/?",
	"rb_back", "stand"
}

--[[
---
---test memory release.
---
local function pause(msg)
	print(msg)
	io.read("*number")
end

local function testMemory()
	pause("press key to start test...")
	local layers = {}
	local layerCount = 10000
	for i = 1, layerCount do
		local layer = Layer.createLayer()
		table.insert(layers, layer)
	end
	pause(#layers .. " layers had created...please see memory...press key to release memory")
	for i = 1, #layers do
		local layer = layers[i]
		layer:dispose()
	end
	pause("released...please make sure of this...")
end

testMemory()
]]

local stage = Stage.getStage()
local layerBackground = Layer.createLayer()
local layerSprites = Layer.createLayer()
stage:addLayer(layerBackground)
stage:addLayer(layerSprites)

local back = Sprite.createSprite("rb_back", "background")
layerBackground:addSprite(back)

local sprite = Sprite.createSprite("stand", "stand")
--layerSprites:addSprite(sprite)
back:addChild(sprite)

local sw = sprite.width
local sh = sprite.height
print("sprite.width=>" .. sw)
print("sprite.height=>" .. sh)

back:setPivot(back.width / 2, back.height / 2)
back.x = back.width / 2
back.y = back.height / 2

print("back.type=>" .. back.type)
print("back.type=>" .. back.color)
print("back.type=>" .. back.alpha)
print("back.type=>" .. back.additive)

--sprite.alpha = 120
--sprite.color = 0xff0000ff
--sprite.additive = 60

local scaleState = 0

--[[
---test events.
local function onClicked1(sender)
	print("onClicked1...")
end

local function onClicked2(sender)
	print("onClicked2...")
end

sprite:addEventListener("click", onClicked1)
sprite:addEventListener("click", onClicked2)
print(sprite:hasEventListener("click"))
print(sprite:getEventListenerCount("click"))
sprite:removeAllEventListener()
sprite:dispatchEvent("click")

local function onStageClicked(sender)
	print("frameRate=>" .. sender.frameRate)
end
stage:addEventListener("click", onStageClicked)
stage:dispatchEvent("click")

---end test events.
--]]

local game = {}

function game.update()
	local rot = back.rotation
	back.rotation = rot + 8
	
	--[[local s = sprite.scale
	local sFactor = 0.06
	if scaleState == 0 then
		s = s - sFactor
		if s <= 0.4 then
			scaleState = 1
		end
	elseif scaleState == 1 then
		s = s + sFactor
		if s >= 1 then
			scaleState = 0
		end
	end
	
	sprite.scale = s]]
	--sprite.frame = sprite.frame + 1
	
	local f = sprite:nextFrame()
	--print(f)
end

function game.drawframe()
	stage:clearCanvas(0)
	stage:draw()
end

function game.touch(what, x, y)
	
end

function game.message(...)
	
end

function game.handle_error(...)
	
end

function game.on_resume()
	
end

function game.on_pause()
	
end

ej.start(game)

--[[
local function pause(msg)
	msg = msg or ''
	print(msg)
	io.read("*number")
end

---
---test metatable
---
local sub = {name="I'm sub"}
local base = {}
setmetatable(sub, base)
--print("sub.name = " .. sub.name)
--print("base.name = " .. base.name)

function base:test()
	print(self)
	print(self.name)
end

function base.__index(tbl, key)
	return base[key]
end

function base.__newindex()
	
end

--!sub:test() --done!不然没法实现继承。
]]

--[[
--
--test memory...
--

pause("input a number to create layers...")
print("test create layer...")
local list = {}
for i = 1, 100000 do
	local layer = {}--Layer.createLayer()
	table.insert(list, layer)
end
print("end test create layer...")

pause("input a number to release layers ")
print("test dispose layer...")
print("#list=>" .. #list)
for i = 1, #list do
	local layer = list[i]
	--layer:dispose()
	list[i] = nil
end
list = nil

print("end test dispose layer...")

pause("now please make sure that the momery is released...")
]]