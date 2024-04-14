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
	
	int width = 2;
	int height = 1;
	
	canvas_initialize(width, height, COLOR_BLACK);
	
	canvas_set_pixel(1, 0, COLOR_WHITE);
	
	canvas_save_to_ppm("test_test");
	
	canvas_cleanup();
	
	puts("All looks good.\n");
	SDL_Quit();
	
	return EXIT_SUCCESS;
}
