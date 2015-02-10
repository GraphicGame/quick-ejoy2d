---
---这个模块存在的意义仅仅是为了向引擎使用者隐藏SimplePackage.
---

local SimplePackage = require "quick.lua.SimplePackage"

local Resources = {}

function Resources.loadPackage(packPath)
	SimplePackage.preload(packPath)
end

function Resources.isPackageLoaded(packPath)
	return SimplePackage.isPackageLoaded(packPath)
end

function Resources.unloadPackage(packPath)
	--@to do...
	assert(false)
end

return Resources