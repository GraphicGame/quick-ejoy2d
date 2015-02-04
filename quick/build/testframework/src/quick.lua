local Stage = require "quick.lua.Stage"
local Layer = require "quick.lua.Layer"
local Sprite = require "quick.lua.Sprite"
local SimplePackage = require "quick.lua.SimplePackage"
local ej = require "ejoy2d"
local fw = require "ejoy2d.framework"

SimplePackage.load {
	pattern = fw.WorkDir.."quick/build/rainblood/res/?",
	--pattern = fw.WorkDir.."res/?",
	"rb_back"
}

local stage = Stage.getStage()
local backgroundLayer = Layer.createLayer()
local spriteLayer = Layer.createLayer()
stage:addLayer(backgroundLayer)
stage:addLayer(spriteLayer)
local sprite = Sprite.createSprite("rb_back", "background")
spriteLayer:addSprite(sprite)

local game = {}

function game.update()
	
end

function game.drawframe()
	sprite:draw()
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