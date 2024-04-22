#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "core/render.h"
#include "core/canvas.h"
#include "core/color.h"
#include "core/tuple.h"

int main(int argc, char **argv) {
	const int width = 900;
	const int height = 550;
	
	canvas_initialize(width, height, COLOR_BLACK);
	
	struct Tuple projectilePos = new_point(.0f, 1.0f, .0f);
	struct Tuple velocity = tuple_mul_f(tuple_norm(new_vector(1.0f, 1.8f, .0f)), 11.25f);
	struct Tuple gravity = new_vector(.0f, -.1f, .0f);
	struct Tuple wind = new_vector(-.01f, .0f, .0f);
	
	while (projectilePos.y > .0f) {
		canvas_set_pixel(
			(int)projectilePos.x,
			(int)(height - projectilePos.y),
			COLOR_RED);
		
		tuple_add_self(&projectilePos, velocity);
		tuple_add_self(&velocity, gravity);
		tuple_add_self(&velocity, wind);
	}
	
	if (render_init(width, height) != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}
	
	uint32_t pixels[width * height];
	canvas_as_argb8888(pixels);
	canvas_cleanup();
	
	render_update_screen(pixels);
	
	render_cleanup();
	
	puts("ALL DONE\n");
	
	return EXIT_SUCCESS;
}
