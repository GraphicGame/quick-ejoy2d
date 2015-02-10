local ej = require "ejoy2d"
local Stage = require "quick.lua.Stage"
local Layer = require "quick.lua.Layer"
local Sprite = require "quick.lua.Sprite"
local Resources = require "quick.lua.Resources"
local Screen = require "quick.lua.Screen"

--舞台
local _stage
--背景层
local _layerBackground
--精灵层
local _layerSprites

---
---初始化舞台
---
local function initStage()
	--创建舞台，舞台是全局唯一的.
	_stage = Stage.getStage()
	--屏幕适配，通过缩放舞台来达到屏幕适配的目的。
	_stage.scale = Screen.width / 960

	--创建两个层次，一个是背景层，一个是精灵层.
	_layerBackground = Layer.createLayer()
	_layerSprites = Layer.createLayer()

	--将两个层次按照顺序放到舞台上
	_stage:addLayer(_layerBackground)
	_stage:addLayer(_layerSprites)
end

local _spriteList = {} --精灵列表
local _soulHero --主角：魂！
---
---初始化精灵
---
local function initSprites()
	--初始化背景
	local background = Sprite.createSprite("background", "background")
	_layerBackground:addSprite(background)
	--初始化精灵
	local robert = Sprite.createSprite("robert", "robert")
	_layerSprites:addSprite(robert)
	table.insert(_spriteList, robert)
	robert.x = 100
	robert.y = 460
	robert.actionName = "stand"
end

---
---初始化游戏
---
local function initGame()
	initStage()   --初始化舞台
	initSprites() --初始化精灵
end

--
--游戏的框架（用的是ejoy2d的原生设计）
--
local game = {}

function game.update()
	--精灵动画
	for i = 1, #_spriteList do
		(_spriteList[i]):nextFrame()
	end
end

function game.drawframe()
	--绘制舞台（含舞台中的所有对象）
	_stage:clearCanvas(0)
	_stage:draw()
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

initGame()
ej.start(game)
