#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "core/canvas.h"
#include "core/color.h"
#include "core/tuple.h"
#include "utils/ppm.h"

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Failed to init SDL. Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	int width = 5;
	int height = 6;
	
	canvas_initialize(width, height);
	
	canvas_set_pixel(0, 0, COLOR_WHITE);
	canvas_set_pixel(1, 0, COLOR_BLACK);
	canvas_set_pixel(2, 0, COLOR_WHITE);
	canvas_set_pixel(3, 0, COLOR_BLACK);
	canvas_set_pixel(4, 0, COLOR_WHITE);
	
	canvas_set_pixel(0, 1, COLOR_BLACK);
	canvas_set_pixel(1, 1, COLOR_WHITE);
	canvas_set_pixel(2, 1, COLOR_BLACK);
	canvas_set_pixel(3, 1, COLOR_WHITE);
	canvas_set_pixel(4, 1, COLOR_BLACK);
	
	canvas_set_pixel(0, 2, COLOR_WHITE);
	canvas_set_pixel(1, 2, COLOR_BLACK);
	canvas_set_pixel(2, 2, COLOR_WHITE);
	canvas_set_pixel(3, 2, COLOR_BLACK);
	canvas_set_pixel(4, 2, COLOR_WHITE);
	
	canvas_set_pixel(0, 3, COLOR_BLACK);
	canvas_set_pixel(1, 3, COLOR_WHITE);
	canvas_set_pixel(2, 3, COLOR_BLACK);
	canvas_set_pixel(3, 3, COLOR_WHITE);
	canvas_set_pixel(4, 3, COLOR_BLACK);
	
	canvas_set_pixel(0, 4, COLOR_WHITE);
	canvas_set_pixel(1, 4, COLOR_BLACK);
	canvas_set_pixel(2, 4, COLOR_WHITE);
	canvas_set_pixel(3, 4, COLOR_BLACK);
	canvas_set_pixel(4, 4, COLOR_WHITE);
	
	canvas_set_pixel(0, 5, COLOR_BLACK);
	canvas_set_pixel(1, 5, COLOR_WHITE);
	canvas_set_pixel(2, 5, COLOR_BLACK);
	canvas_set_pixel(3, 5, COLOR_WHITE);
	canvas_set_pixel(4, 5, COLOR_BLACK);
	
	int pixelCount = canvas_get_pixel_count();
	int a[pixelCount * 3];
	canvas_get_as_int_array(a);
	
	ppm_save("test_test", width, height, a);
	
	canvas_cleanup();
	
	puts("All looks good.\n");
	SDL_Quit();
	
	return EXIT_SUCCESS;
}
