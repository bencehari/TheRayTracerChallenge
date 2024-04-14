#include "canvas.h"

#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "../utils/ppm.h"

#ifdef AD_CHK
	#include "../utils/log.h"
#endif

static int width;
static int height;
static struct Color clearColor;
static struct Color* canvas;

void canvas_clear(void);

bool canvas_initialize(int _width, int _height, struct Color _clearColor) {
#ifdef AD_CHK
	if (_width < 1 || _height < 1) {
		LOG_E("init: width or height lower than 1!");
		return false;
	}
#endif // AD_CHK
	
	canvas = malloc(sizeof(struct Color) * _width * _height);
	if (canvas == NULL) {
		printf("Couldn't allocate enough memory for canvas (%lu bytes).", sizeof(struct Color) * _width * _height);
		return false;
	}
	
	width = _width;
	height = _height;
	clearColor = _clearColor;
	
	canvas_clear();
	
	return false;
}

void canvas_clear(void) {
	for (int i = 0; i < width + height; i++) {
		canvas[i] = clearColor;
	}
}

void canvas_cleanup(void) {
	if (width == 0 || height == 0) return;
	
	free(canvas);
	width = height = 0;
}

void canvas_set_pixel(int _x, int _y, struct Color _c) {
#ifdef AD_CHK
	if (_x < 0 || _x >= width || _y < 0 || _y >= height) {
		LOG_W("set_pixel: _x or _y out of bounds (canvas).");
		return;
	}
#endif // AD_CHK
	canvas[_y * width + _x] = _c;
}

static void canvas_get_as_int_array(uint8_t _colors[]) {
	for (int is = 0, id = 0; is < width * height; is++, id += 3) {
		_colors[id] = (uint8_t)(canvas[is].r * 255);
		_colors[id + 1] = (uint8_t)(canvas[is].g * 255);
		_colors[id + 2] = (uint8_t)(canvas[is].b * 255);
	}
}

void canvas_save_to_ppm(const char* _name) {
	uint8_t a[width * height * 3];
	canvas_get_as_int_array(a);
	
	ppm_save(_name, width, height, a);
}
