#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>

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
	
	// SDL
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Failed to init SDL. Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	SDL_Window* window = SDL_CreateWindow(
		"The Ray Tracing Challenge",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, 0);
	if (window == NULL) {
		printf("Failed to create SDL window. Error: %s\n", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) {
		printf("Failed to create SDL renderer. Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	SDL_Texture* texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STATIC,
		width, height);
	
	uint32_t pixels[width * height];
	canvas_as_argb8888(pixels);
	canvas_cleanup();
	
	bool quit = false;
	SDL_Event event;
	while (!quit) {
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_QUIT: quit = true; break;
		}
		
		SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(uint32_t));
		
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	puts("ALL DONE\n");
	
	return EXIT_SUCCESS;
}
