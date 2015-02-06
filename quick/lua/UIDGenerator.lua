local UIDGenerator = {}

local index = 0

function UIDGenerator.generateUID()
	index = index + 1
	return index
end

return UIDGenerator