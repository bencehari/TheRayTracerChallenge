#include "tests.h"

#include <stdio.h>

#include "../core/matrices.h"
#include "../utils/consc.h"

#define EVALUATE(_expr) ((_expr) ? (AC_GREEN "PASS" AC_RESET) : (AC_RED "FAIL" AC_RESET))

void test_translation(void);
void test_inverse_translation(void);

void test_transformations(void) {
	test_translation();
	test_inverse_translation();
}

void test_translation(void) {
	union Matrix4x4 transform = m4x4_translation(new_point(5, -3, 2));
	union Tuple point = new_point(-3, 4, 5);
	union Tuple res = m4x4_mul_tuple(&transform, &point);
	
	printf("Multiplying by a translation matrix: %s\n", EVALUATE(tuple_eq(res, new_point(2, 1, 7))));
}

void test_inverse_translation(void) {
	union Matrix4x4 transform = m4x4_translation(new_point(5, -3, 2));
	union Matrix4x4 inverse = m4x4_inverse(&transform);
	union Tuple point = new_point(-3, 4, 5);
	union Tuple res = m4x4_mul_tuple(&inverse, &point);
	
	printf("Multiplying by the inverse of a translation matrix: %s\n", EVALUATE(tuple_eq(res, new_point(-8, 7, 3))));
}
