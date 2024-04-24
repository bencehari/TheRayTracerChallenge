#include "tests.h"

#include <stdio.h>

#include "../core/matrices.h"
#include "../utils/consc.h"

#define EVALUATE(_expr) ((_expr) ? (AC_GREEN "PASS" AC_RESET) : (AC_RED "FAIL" AC_RESET))

void test_translation(void);
void test_inverse_translation(void);
void test_translate_vector(void);
void test_scale(void);
void test_scale_vector(void);
void test_inverse_scale(void);
void test_negative_scale(void);

void test_transformations(void) {
	test_translation();
	test_inverse_translation();
	test_translate_vector();
	test_scale();
	test_scale_vector();
	test_inverse_scale();
	test_negative_scale();
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

void test_translate_vector(void) {
	union Matrix4x4 transform = m4x4_translation(new_point(5, -3, 2));
	union Tuple vector = new_vector(-3, 4, 5);
	union Tuple res = m4x4_mul_tuple(&transform, &vector);
	
	printf("A scaling matrix applied to a point: %s\n", EVALUATE(tuple_eq(res, vector)));
}

void test_scale(void) {
	union Matrix4x4 transform = m4x4_scaling(new_point(2, 3, 4));
	union Tuple point = new_point(-4, 6, 8);
	union Tuple res = m4x4_mul_tuple(&transform, &point);
	
	printf("Translation does not affect vectors: %s\n", EVALUATE(tuple_eq(res, new_point(-8, 18, 32))));
}

void test_scale_vector(void) {
	union Matrix4x4 transform = m4x4_scaling(new_point(2, 3, 4));
	union Tuple vector = new_vector(-4, 6, 8);
	union Tuple res = m4x4_mul_tuple(&transform, &vector);
	
	printf("A scaling matrix applied to a vector: %s\n", EVALUATE(tuple_eq(res, new_vector(-8, 18, 32))));
}

void test_inverse_scale(void) {
	union Matrix4x4 transform = m4x4_scaling(new_point(2, 3, 4));
	union Matrix4x4 inverse = m4x4_inverse(&transform);
	union Tuple vector = new_vector(-4, 6, 8);
	union Tuple res = m4x4_mul_tuple(&inverse, &vector);
	
	printf("Multiplying by the inverse of a scaling matrix: %s\n", EVALUATE(tuple_eq(res, new_vector(-2, 2, 2))));
}

void test_negative_scale(void) {
	union Matrix4x4 transform = m4x4_scaling(new_point(-1, 1, 1));
	union Tuple point = new_point(2, 3, 4);
	union Tuple res = m4x4_mul_tuple(&transform, &point);
	
	printf("Reflection is scaling by a negative value: %s\n", EVALUATE(tuple_eq(res, new_point(-2, 3, 4))));
}
