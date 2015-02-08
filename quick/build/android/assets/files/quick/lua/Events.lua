local UIDGenerator = require "quick.lua.UIDGenerator"
local ObjectsKeeper = require "quick.lua.ObjectsKeeper"

local Events = {}
local funcs = {}
local funcsInverse = {}

function _G.__event_callback_entry_func__(funcKey, sender)
	print("func:" .. funcKey .. " called...")
	local func = funcs[funcKey]
	if not func then
		print("Couldn't find this funcKey=>" .. funcKey)
		return
	end
	
	local senderObj = ObjectsKeeper.fetch(sender)
	func(senderObj)
end

function Events.wrapFunc(func)
	if funcsInverse[func] then
		return funcsInverse[func]
	end
	
	local uid = UIDGenerator.generateUID()
	local funcKey = "func_" .. uid
	funcs[funcKey] = func
	funcsInverse[func] = funcKey
	return funcKey
end

function Events.getFunc(funcKey)
	return funcs[funcKey]
end

return Events