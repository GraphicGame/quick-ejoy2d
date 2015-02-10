local FW = require "ejoy2d.framework"
local setmetatable = setmetatable

local Screen = {}
local screenMeta = {}
setmetatable(Screen, screenMeta)

function screenMeta.__index(tbl, key)
	local get = FW[key]
	if get then
		return get
	end
	error("[Screen] Unsupport get method : " .. key)
end

function screenMeta.__newindex(tbl, key, v)
	error("[Screen] Unsupport set method : " .. key)
end

return Screen