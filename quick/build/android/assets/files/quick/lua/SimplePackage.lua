-- It's a simple sprite package warpper, use your own asset format instead.

local ejoy2d = require "ejoy2d"
local ppm = require "ejoy2d.ppm"
--local pack = require "ejoy2d.spritepack"
local pack = require "quick.lua.SpritePack"
local sprite = require "ejoy2d.sprite"

local png = require "ejoy2d.png"
local jpg = require "ejoy2d.jpg"
local fw = require "ejoy2d.framework"

-- This limit defined in texture.c
local MAX_TEXTURE = 128

local textures = {}
local packages = {}

local spack = {}
local package_pattern

local function require_tex(fileName, texType)
	local tex = #textures
	assert(tex < MAX_TEXTURE)
	table.insert(textures, fileName)

	if texType == "ppm" then
		ppm.texture(tex, fileName)
	elseif texType == "png" then
		png.texture(tex, fileName)
	elseif texType == "jpg" then
		jpg.texture(tex, fileName)
	else
		--error('unknown texture type...')
		print("fileName=>" .. fileName)
	end

	return tex
end

function spack.path(pattern)
	package_pattern = pattern
end

local function realname(filename)
	--assert(package_pattern, "Need a pattern")
	if package_pattern == nil then
		package_pattern = fw.WorkDir .. "res/?"
		--package_pattern = fw.WorkDir .. "quick/demos/kofanim/res/?"
	end
	return string.gsub(package_pattern,"([^?]*)?([^?]*)","%1"..filename.."%2")
end

function spack.preload(packname)
	if packages[packname] then
		return packages[packname]
	end
	local p = {}
	local filename = realname(packname)
	p.meta = assert(pack.pack(dofile(filename .. ".lua")))

	p.tex = {}
	for i=1,p.meta.texture do
		local texType = p.meta.textureType[i]
		p.tex[i] = require_tex(filename .. "." .. i, texType)
	end
	pack.init(packname, p.tex, p.meta)
	packages[packname] = p
end

function spack.preload_raw(packname)
	if packages[packname] then
		return packages[packname]
	end
	local p = {}
	local filename = realname(packname)
	local data = io.open(filename..".raw", "rb"):read("*a")
	p.meta = assert(pack.import(data))

	p.tex = {}
	for i=1,p.meta.texture do
		--local texType = p.meta.textureType[i]
		p.tex[i] = require_tex(filename .. "." .. i, nil) --@to do...
	end
	pack.init(packname, p.tex, p.meta)
	packages[packname] = p
end

function ejoy2d.sprite(packname, name)
	if packages[packname] == nil then
		spack.preload(packname)
	end
	return sprite.new(packname, name)
end

function ejoy2d.load_texture(filename)
	return require_tex(filename)
end

function spack.load(tbl)
	spack.path(assert(tbl.pattern))
	for _,v in ipairs(tbl) do
		spack.preload(v)
		collectgarbage "collect"
	end
end

function spack.load_raw(tbl)
	spack.path(assert(tbl.pattern))
	for _,v in ipairs(tbl) do
		spack.preload_raw(v)
	end
	collectgarbage "collect"
end

function spack.texture(packname, index)
	if packages[packname] == nil then
		spack.preload(packname)
	end
	return packages[packname].tex[index or 1]
end

function spack.export(outdir, tbl)
	spack.path(assert(tbl.pattern))
	for _, packname in ipairs(tbl) do
		print("packname    ", packname, outdir, tbl.pattern)
		local filename = string.gsub(outdir..tbl.pattern,
				"([^?]*)?([^?]*)", "%1"..packname.."%2")
		print("spack.export     ",  filename.. ".raw")

		local meta = assert(pack.pack(dofile(filename .. ".lua")))
		local output = pack.export(meta)

		local file = io.open(filename .. ".raw", "w+")
		file:write(output)
		file:close()
	end
end

function spack.isPackageLoaded(packPath)
	return (packages[packPath] ~= nil)
end

return spack
