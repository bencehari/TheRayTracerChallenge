#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "core/canvas.h"
#include "core/color.h"
#include "core/tuple.h"

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Failed to init SDL. Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	int width = 900;
	int height = 550;
	
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
	
	canvas_save_to_ppm("test_test");
	
	canvas_cleanup();
	
	puts("All looks good.\n");
	SDL_Quit();
	
	return EXIT_SUCCESS;
}
