#include "tests.h"

#include <stdlib.h> // EXIT_*

#include "../core/render.h"
#include "../core/canvas.h"
#include "../core/color.h"
#include "../core/tuple.h"
#include "../core/matrices.h"

int test_draw_trajectory(void) {
	const int width = 900;
	const int height = 550;
	
	canvas_initialize(width, height, COLOR_BLACK);
	
	union Tuple projectilePos = new_point(0.0f, 1.0f, 0.0f);
	union Tuple velocity = tuple_mul_f(tuple_norm(new_vector(1.0f, 1.8f, 0.0f)), 11.25f);
	union Tuple gravity = new_vector(0.0f, -0.1f, 0.0f);
	union Tuple wind = new_vector(-0.01f, 0.0f, 0.0f);
	
	while (projectilePos.y > 0.0f) {
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
	
	// render_update_screen(pixels);
	render_set_screen(pixels);
	
	render_cleanup();
	
	return EXIT_SUCCESS;
}
