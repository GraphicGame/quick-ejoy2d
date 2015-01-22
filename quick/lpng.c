#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>

#include "3rd/libpng/png.h"
#include "lpng.h"
#include "texture.h"
#include "array.h"

#define PNG_BYTES_TO_CHECK 4

struct png {
	int type;
	int channel;
	int width;
	int height;
	uint8_t *buffer;
};

static int
_loadpng(const char* filename, struct png* png, png_byte *out_pixel_depth, png_byte *out_chanels_count) {
	// open file
	FILE* fp = fopen(filename, "rb");
	if (!fp) { return 0; }

	// init libpng
	png_structp png_ptr;
	png_infop info_ptr;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	info_ptr = png_create_info_struct(png_ptr);
	setjmp(png_jmpbuf(png_ptr));

	// check png legality
	int temp;
	char temp2[PNG_BYTES_TO_CHECK];

	temp = fread(temp2, 1, PNG_BYTES_TO_CHECK, fp);
	if (temp < PNG_BYTES_TO_CHECK) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return 0;
	}

	temp = png_sig_cmp((png_bytep)temp2, (png_size_t)0, PNG_BYTES_TO_CHECK);
	if (temp != 0) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return 0;
	}

	// read png data
	rewind(fp);
	png_init_io(png_ptr, fp);
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

	// get image info
	int w = png_get_image_width(png_ptr, info_ptr);
	int h = png_get_image_height(png_ptr, info_ptr);
	int color_type = png_get_color_type(png_ptr, info_ptr);

	//png texture-format.
	*out_pixel_depth = png_get_bit_depth(png_ptr, info_ptr);
	*out_chanels_count = png_get_channels(png_ptr, info_ptr);

	png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);

	switch (color_type) {
	case PNG_COLOR_TYPE_RGB_ALPHA:
		png->type = PNG_RGBA;
		png->channel = 4;
		png->buffer = (uint8_t*)malloc(w*h * 4);
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				int k = (i*w + j) * 4;
				uint8_t alpha = row_pointers[i][j * 4 + 3];
				png->buffer[k + 0] = row_pointers[i][j * 4 + 0] * alpha / 255; // red
				png->buffer[k + 1] = row_pointers[i][j * 4 + 1] * alpha / 255; // green
				png->buffer[k + 2] = row_pointers[i][j * 4 + 2] * alpha / 255; // blue
				png->buffer[k + 3] = alpha; // alpha
			}
		}
		break;

	case PNG_COLOR_TYPE_RGB:
		png->type = PNG_RGB;
		png->channel = 3;
		png->buffer = (uint8_t*)malloc(w*h * 3);
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				int k = (i*w + j) * 3;
				png->buffer[k + 0] = row_pointers[i][j * 3 + 0]; // red
				png->buffer[k + 1] = row_pointers[i][j * 3 + 1]; // green
				png->buffer[k + 2] = row_pointers[i][j * 3 + 2]; // blue
			}
		}
		break;

	default:
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return 0;
	}

	png_destroy_read_struct(&png_ptr, &info_ptr, 0);

	png->width = w;
	png->height = h;
	return 1;
}

static TEXTURE_FORMAT
_get_png_texture_format(png_byte pixel_depth, png_byte chanels_count) {
	if (chanels_count == 3) {
		return TEXTURE_RGB;
	} else if (chanels_count == 4) {
		if (pixel_depth == 8)
			return TEXTURE_RGBA8;
		else if (pixel_depth == 4)
			return TEXTURE_RGBA4;
	}
}

static int
lua_loadtexture(lua_State *L) {
	int id = (int)luaL_checkinteger(L, 1);
	size_t sz = 0;
	const char *filename = luaL_checklstring(L, 2, &sz);
	ARRAY(char, tmp, sz + 5);
	sprintf(tmp, "%s.png", filename);
	
	struct png png;
	png_byte pixel_depth, chanels_count;
	int success = _loadpng(tmp, &png, &pixel_depth, &chanels_count);
	if (!success) {
		return luaL_error(L, "Can't open %s.png", filename);
	}

	int tex_format = _get_png_texture_format(pixel_depth, chanels_count);
	const char *err = texture_load(id, (TEXTURE_FORMAT)tex_format, png.width, png.height, png.buffer, lua_toboolean(L, 3));
	free(png.buffer);
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
lua_png(lua_State *L) {
	luaL_Reg l[] = {
		{ "texture", lua_loadtexture },
		{ "unload", lua_unload_tex },
		{ NULL, NULL },
	};

	luaL_newlib(L, l);

	return 1;
}