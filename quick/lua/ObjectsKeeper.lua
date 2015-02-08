
local ObjectsKeeper = {}

local objs = {}

function ObjectsKeeper.keep(lud, obj)
	objs[lud] = obj
end

function ObjectsKeeper.fetch(lud)
	return objs[lud]
end

function ObjectsKeeper.dispose(lud)
	objs[lud] = nil
end

return ObjectsKeeper