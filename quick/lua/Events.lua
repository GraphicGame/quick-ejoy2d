local UIDGenerator = require "quick.lua.UIDGenerator"

local Events = {}
local funcs = {}
local funcsMeta = {}

function _G.__event_callback_entry_func__(funcKey, sender)
	local func = funcs[funcKey]
	if not func then
		error("Couldn't find this funcKey=>" .. funcKey)
		return
	end
	func(sender)
end

function Events.wrapFunc(func)
	local uid = UIDGenerator.generateUID()
	local funcKey = "func_" .. uid
	funcs[funcKey] = func
	return funcKey
end

function Events.getFunc(funcKey)
	return funcs[funcKey]
end

return Events