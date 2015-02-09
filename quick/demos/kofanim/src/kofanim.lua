local ej = require "ejoy2d"
local Stage = require "quick.lua.Stage"
local Layer = require "quick.lua.Layer"
local Sprite = require "quick.lua.Sprite"
local Resources = require "quick.lua.Resources"

--��̨
local _stage
--������
local _layerBackground
--�����
local _layerSprites

---
---��ʼ����̨
---
local function initStage()
	--������̨����̨��ȫ��Ψһ��.
	_stage = Stage.getStage()

	--����������Σ�һ���Ǳ����㣬һ���Ǿ����.
	_layerBackground = Layer.createLayer()
	_layerSprites = Layer.createLayer()

	--��������ΰ���˳��ŵ���̨��
	_stage:addLayer(_layerBackground)
	_stage:addLayer(_layerSprites)
end

local _spriteList = {} --�����б�

---
---��ʼ������
---
local function initSprites()
	--��ʼ������
	local background = Sprite.createSprite("background", "background")
	_layerBackground:addSprite(background)
	--��ʼ������
	local mary = Sprite.createSprite("mary", "mary")
	_layerSprites:addSprite(mary)
	table.insert(_spriteList, mary)
	
	mary.scale = 1.6
	mary.x = 100
	mary.y = 460
	mary.actionName = "stand"
end

---
---��ʼ����Ϸ
---
local function initGame()
	initStage()   --��ʼ����̨
	initSprites() --��ʼ������
end

--
--��Ϸ�Ŀ�ܣ��õ���ejoy2d��ԭ����ƣ�
--
local game = {}

function game.update()
	--���鶯��
	for i = 1, #_spriteList do
		(_spriteList[i]):nextFrame()
	end
end

function game.drawframe()
	--������̨������̨�е����ж���
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
