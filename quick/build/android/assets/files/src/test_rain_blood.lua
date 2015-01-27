local ej = require "ejoy2d"
local fw = require "ejoy2d.framework"
local pack = require "ejoy2d.simplepackage"

pack.load {
	--pattern = fw.WorkDir.."quick/build/rainblood/res/?",
	pattern = fw.WorkDir.."res/?",
	"rb_back", "stand", "run", "stoprun"
}

local A_STAND = 0
local A_RUN = 1
local A_STOPRUN = 2

local function getSprite()
	local sprite = {};
	sprite.actions = {}
	sprite.actions[A_STAND] = ej.sprite("stand", "stand")
	sprite.actions[A_RUN] = ej.sprite("run", "run")
	sprite.actions[A_STOPRUN] = ej.sprite("stoprun", "stoprun")
	sprite.currentActionID = -1
	sprite.ps = { x = 0, y = 0, sx = 1, sy = 1 }

	function sprite:setPs(ps_tbl)
		self.ps = ps_tbl;
	end

	function sprite:setAction(actionID)
		if self.currentActionID == actionID then
			return
		end
		self.currentActionID = actionID;
	end

	function sprite:animate()
		local f = self.actions[self.currentActionID].frame
		self.actions[self.currentActionID].frame = f + 1
	end

	function sprite:draw() 
		self.actions[self.currentActionID]:draw(self.ps)
	end

	return sprite;
end

local DelayCall = {}
DelayCall.delays = {}
function DelayCall:addDelay(delay, func)
	local delays = self.delays
	if delays[delay] == nil then
		delays[delay] = {}
	end

	local existSame = false
	local delayArray = delays[delay];
	for i = 1, #delayArray do
		local d = delayArray[i]
		if d ~= nil and d.f == func then
			existSame = true
			break
		end
	end
	if not existSame then
		table.insert(delays[delay], {f = func, now = os.clock()})
		print("delay func inserted.")
	end
end

function DelayCall:update()
	local now = os.clock()
	local delays = self.delays
	for k, v in pairs(delays) do
		local delayTime = k
		local delayArray = v
		for i = 1, #delayArray do
			local d = delayArray[i]
			if d ~= nil then
				local timePassed = now - d.now
				if timePassed >= delayTime then
					if d.f ~= nil then
						d.f()
						table.remove(delayArray, i)
						i = i - 1
						print('remove delay func...')
					end
				end
			end
		end
	end
end

local function getHero()
	
end

local hero = getSprite();
local heroMoving = false
local heroMovingTargetPosX = 0
local heroMoveSpeed = 12

hero.ps.x = 80
hero.ps.y = 460
hero:setAction(A_STAND);

local heroList = {}
local startX = 80
local startY = 350
for i = 1, 2 do
	for j = 1, 30 do
		local hero = getSprite();
		hero.ps.x = startX
		hero.ps.y = startY
		hero:setAction(A_STAND)
		startX = startX + 60;
		table.insert(heroList, hero);
	end
	startX = 80
	startY = startY + 40
end

local background = ej.sprite("rb_back", "background");
local backgroud_pos = { x = 0, y = 8, scale = 1};

local label = ej.sprite("rb_back", "label");
local label_pos = {x = 10, y = 10, scale = 1};
label.text = " HaHaHa!! Engine Demo!!";

local function delayStopMoving()
	print("delay func called.")
	heroMoving = false
	hero:setAction(A_STAND)
end

local function onTouch(x, y)
	heroMoving = true
	hero:setAction(A_RUN)
	heroMovingTargetPosX = x

	if hero.ps.x <= x then
		if hero.ps.sx == -1 then
			hero.ps.x = hero.ps.x - 100
		end
		hero.ps.sx = 1
		heroMoveSpeed = math.abs(heroMoveSpeed)
	else
		if hero.ps.sx == 1 then
			hero.ps.x = hero.ps.x + 100
		end
		hero.ps.sx = -1
		heroMoveSpeed = -math.abs(heroMoveSpeed)
	end
end

local game = {}

function game.update()
	DelayCall:update()
	hero:animate()
	if heroMoving then
		hero.ps.x = hero.ps.x + heroMoveSpeed;
		if (heroMoveSpeed > 0 and hero.ps.x >= heroMovingTargetPosX - 120) or (heroMoveSpeed < 0 and hero.ps.x <= heroMovingTargetPosX + 120) then
			hero:setAction(A_STOPRUN);
			DelayCall:addDelay(0.8, delayStopMoving)
		end
	end

	for i = 1, #heroList do
		local hero = heroList[i];
		hero:animate()
	end
end

function game.drawframe()
	ej.clear(0xff808080)	-- clear (0.5,0.5,0.5,1) gray
	background:draw(backgroud_pos);

	for i = 1, #heroList do
		local hero = heroList[i];
		hero:draw()
	end

	hero:draw()
	label:draw(label_pos)
end

function game.touch(what, x, y)
	onTouch(x, y)
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