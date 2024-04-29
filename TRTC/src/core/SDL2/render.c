#include "../render.h"

#include <stdio.h>
#include <SDL2/SDL.h>

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* texture;

static int width;
static int height;

int render_init(const int _width, const int _height) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Failed to init SDL. Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	window = SDL_CreateWindow(
		"The Ray Tracing Challenge",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_width, _height, 0);
	if (window == NULL) {
		printf("Failed to create SDL window. Error: %s\n", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) {
		printf("Failed to create SDL renderer. Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STATIC,
		_width, _height);
		
	width = _width;
	height = _height;
	
	return EXIT_SUCCESS;
}

void render_set_screen(uint32_t _pixels[]) {
	SDL_UpdateTexture(texture, NULL, _pixels, width * sizeof(uint32_t));
	
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	
	// testing purposes only until proper input handling
	SDL_Event event;
	while (1) {
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_QUIT: return;
		}
	}
}

// NOT TESTED
void render_update_screen(uint32_t* (*_getPixels)(void)) {
	bool quit = false;
	SDL_Event event;
	while (!quit) {
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_QUIT: quit = true; break;
		}
		
		uint32_t* pixels = _getPixels();
		SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(uint32_t));
		
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
}

void render_cleanup(void) {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
