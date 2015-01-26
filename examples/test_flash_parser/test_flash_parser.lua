local ej = require "ejoy2d"
local fw = require "ejoy2d.framework"
local pack = require "ejoy2d.simplepackage"

pack.load {
	pattern = fw.WorkDir..[[examples/test_flash_parser/asset/?]],
	"type1_ej",
}

local obj = ej.sprite("type1_ej","robot_t1")
obj.action = "act1";

local game = {}
local screencoord = { x = 0, y = 0, scale = 1 }

function game.update()
	obj.frame = obj.frame + 1
end

function game.drawframe()
	ej.clear(0xff808080)	-- clear (0.5,0.5,0.5,1) gray
	obj:draw(screencoord)
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