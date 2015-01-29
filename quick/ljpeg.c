#include <lua.h>
#include <lauxlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "3rd/libjpeg/jpeglib.h"
#include "ljpeg.h"
#include "texture.h"
#include "array.h"

struct jpeg {
	int width;
	int height;
	uint8_t *buffer;
};

static int 
_loadjpeg(const char *filename, struct jpeg *jpeg) {
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	FILE *fp;
	JSAMPARRAY buffer;
	int row_width;

	unsigned char *tmp = NULL;

	cinfo.err = jpeg_std_error(&jerr);

	if ((fp = fopen(filename, "rb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		return 0;
	}

	jpeg_create_decompress(&cinfo);

	/* Specify data source for decompression */
	jpeg_stdio_src(&cinfo, fp);

	/* Read file header, set default decompression parameters */
	(void)jpeg_read_header(&cinfo, TRUE);
	jpeg->width = cinfo.image_width;
	jpeg->height = cinfo.image_height;

	/* Start decompressor */
	(void)jpeg_start_decompress(&cinfo);

	row_width = cinfo.output_width * cinfo.output_components;

	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr)&cinfo, JPOOL_IMAGE, row_width, 1);

	jpeg->buffer = (unsigned char *)malloc(row_width * cinfo.output_height);
	memset(jpeg->buffer, 0, row_width * cinfo.output_height);
	tmp = jpeg->buffer;

	/* Process data */
	while (cinfo.output_scanline < cinfo.output_height) {
		(void)jpeg_read_scanlines(&cinfo, buffer, 1);

		memcpy(tmp, *buffer, row_width);
		tmp += row_width;
	}

	(void)jpeg_finish_decompress(&cinfo);

	jpeg_destroy_decompress(&cinfo);

	/* Close files, if we opened them */
	fclose(fp);

	return 1;
}

static int
lua_loadtexture(lua_State *L) {
	int id = (int)luaL_checkinteger(L, 1);
	size_t sz = 0;
	const char *filename = luaL_checklstring(L, 2, &sz);
	ARRAY(char, tmp, sz + 5);
	sprintf(tmp, "%s.jpg", filename);

	struct jpeg jpeg;
	int success = _loadjpeg(tmp, &jpeg);
	if (!success) {
		return luaL_error(L, "Can't open %s.jpg", filename);
	}
	
	//Here we assume that the .jpg file is RGB format.
	const char *err = texture_load(id, TEXTURE_RGB, jpeg.width, jpeg.height, jpeg.buffer, lua_toboolean(L, 3));
	free(jpeg.buffer);
	if (err) {
		return luaL_error(L, "%s", err);
	}

	return 0;
}

static int
lua_unload_tex(lua_State *L) {
	int id = (int)luaL_checkinteger(L, 1);
	texture_unload(id);
	return 0;
}

int
lua_jpeg(lua_State *L) {
	luaL_Reg l[] = {
		{ "texture", lua_loadtexture },
		{ "unload", lua_unload_tex },
		{ NULL, NULL },
	};

	luaL_newlib(L, l);

	return 1;
}