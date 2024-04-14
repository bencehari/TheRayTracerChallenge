#include "canvas.h"

#include <stdio.h>
#include <stdlib.h>

#include "color.h"

static int width;
static int height;
static struct Color* canvas;

bool canvas_initialize(int _width, int _height) {
	canvas = malloc(sizeof(struct Color) * _width * _height);
	if (canvas == NULL) {
		printf("Couldn't allocate enough memory for canvas (%lu bytes).", sizeof(struct Color) * _width * _height);
		return false;
	}
	
	width = _width;
	height = _height;
	
	return false;
}

void canvas_cleanup(void) {
	if (width == 0 || height == 0) return;
	
	free(canvas);
	width = height = 0;
}

void canvas_set_pixel(int _x, int _y, struct Color _c) {
	canvas[_y * width + _x] = _c;
}

int canvas_get_pixel_count(void) {
	return width * height;
}

void canvas_get_as_int_array(uint8_t _colors[]) {
	for (int is = 0, id = 0; is < width * height; is++, id += 3) {
		_colors[id] = (uint8_t)(canvas[is].r * 255);
		_colors[id + 1] = (uint8_t)(canvas[is].g * 255);
		_colors[id + 2] = (uint8_t)(canvas[is].b * 255);
	}
}
