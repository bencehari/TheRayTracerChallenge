#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tests/tests.h"

int main(int argc, char **argv) {
	// if (test_draw_trajectory() != EXIT_SUCCESS) return EXIT_FAILURE;
	// test_matrices();
	test_transformations();
	
	puts("ALL DONE\n");
	
	return EXIT_SUCCESS;
}
