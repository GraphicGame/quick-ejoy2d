---
---���ģ����ڵ����������Ϊ��������ʹ��������SimplePackage.
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