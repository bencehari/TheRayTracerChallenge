#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "core/tuple.h"

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Failed to init SDL. Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	puts("All looks good.\n");
	SDL_Quit();
	
	return EXIT_SUCCESS;
}
