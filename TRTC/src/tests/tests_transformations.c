#include "tests.h"

#include <stdio.h>
#include <math.h>

#include "../core/matrices.h"
#include "../utils/consc.h"

#define EVALUATE(_expr) ((_expr) ? (AC_GREEN "PASS" AC_RESET) : (AC_RED "FAIL" AC_RESET))
#define RESULT(_text, _eval_expr) (printf(_text": %s\n", EVALUATE((_eval_expr))))

void test_translation(void);
void test_inverse_translation(void);
void test_translate_vector(void);
void test_scale(void);
void test_scale_vector(void);
void test_inverse_scale(void);
void test_negative_scale(void);
void test_rotation(void);
void test_inverse_rotation(void);

void test_transformations(void) {
	test_translation();
	test_inverse_translation();
	test_translate_vector();
	test_scale();
	test_scale_vector();
	test_inverse_scale();
	test_negative_scale();
	test_rotation();
	test_inverse_rotation();
}

// ~~~~~~~~~~~
// Utils
// ~~~~~~~~~~~

static const float EPSILON = 0.00001f;

static bool feq(float a, float b) {
	return fabs(a - b) < EPSILON;
}

static bool eq_t(const union Tuple _t0, const union Tuple _t1) {
	return
		feq(_t0.e[ 0], _t1.e[ 0]) &&
		feq(_t0.e[ 1], _t1.e[ 1]) &&
		feq(_t0.e[ 2], _t1.e[ 2]);
}

// ~~~~~~~~~~~
// Tests
// ~~~~~~~~~~~

void test_translation(void) {
	union Matrix4x4 transform = m4x4_translation(new_point(5.0f, -3.0f, 2.0f));
	union Tuple point = new_point(-3.0f, 4.0f, 5.0f);
	union Tuple res = m4x4_mul_tuple(&transform, &point);
	
	RESULT("Multiplying by a translation matrix", tuple_eq(res, new_point(2.0f, 1.0f, 7.0f)));
}

void test_inverse_translation(void) {
	union Matrix4x4 transform = m4x4_translation(new_point(5.0f, -3.0f, 2.0f));
	union Matrix4x4 inverse = m4x4_inverse(&transform);
	union Tuple point = new_point(-3.0f, 4.0f, 5.0f);
	union Tuple res = m4x4_mul_tuple(&inverse, &point);
	
	RESULT("Multiplying by the inverse of a translation matrix", tuple_eq(res, new_point(-8.0f, 7.0f, 3.0f)));
}

void test_translate_vector(void) {
	union Matrix4x4 transform = m4x4_translation(new_point(5.0f, -3.0f, 2.0f));
	union Tuple vector = new_vector(-3.0f, 4.0f, 5.0f);
	union Tuple res = m4x4_mul_tuple(&transform, &vector);
	
	RESULT("A scaling matrix applied to a point", tuple_eq(res, vector));
}

void test_scale(void) {
	union Matrix4x4 transform = m4x4_scaling(new_point(2.0f, 3.0f, 4.0f));
	union Tuple point = new_point(-4.0f, 6.0f, 8.0f);
	union Tuple res = m4x4_mul_tuple(&transform, &point);
	
	RESULT("Translation does not affect vectors", tuple_eq(res, new_point(-8.0f, 18.0f, 32.0f)));
}

void test_scale_vector(void) {
	union Matrix4x4 transform = m4x4_scaling(new_point(2.0f, 3.0f, 4.0f));
	union Tuple vector = new_vector(-4.0f, 6.0f, 8.0f);
	union Tuple res = m4x4_mul_tuple(&transform, &vector);
	
	RESULT("A scaling matrix applied to a vector", tuple_eq(res, new_vector(-8.0f, 18.0f, 32.0f)));
}

void test_inverse_scale(void) {
	union Matrix4x4 transform = m4x4_scaling(new_point(2.0f, 3.0f, 4.0f));
	union Matrix4x4 inverse = m4x4_inverse(&transform);
	union Tuple vector = new_vector(-4.0f, 6.0f, 8.0f);
	union Tuple res = m4x4_mul_tuple(&inverse, &vector);
	
	RESULT("Multiplying by the inverse of a scaling matrix", tuple_eq(res, new_vector(-2.0f, 2.0f, 2.0f)));
}

void test_negative_scale(void) {
	union Matrix4x4 transform = m4x4_scaling(new_point(-1.0f, 1.0f, 1.0f));
	union Tuple point = new_point(2.0f, 3.0f, 4.0f);
	union Tuple res = m4x4_mul_tuple(&transform, &point);
	
	RESULT("Reflection is scaling by a negative value", tuple_eq(res, new_point(-2.0f, 3.0f, 4.0f)));
}

void test_rotation(void) {
	union Tuple point = new_point(0.0f, 1.0f, 0.0f);
	union Matrix4x4 halfQuarter = m4x4_rotation_x(M_PI / 4.0f);
	union Matrix4x4 fullQuarter = m4x4_rotation_x(M_PI / 2.0f);
	
	bool expected =
		eq_t(m4x4_mul_tuple(&halfQuarter, &point), new_point(0.0f, sqrtf(2.0f) / 2.0f, sqrtf(2.0f) / 2.0f)) &&
		eq_t(m4x4_mul_tuple(&fullQuarter, &point), new_point(0.0f, 0.0f, 1.0f));
	
	RESULT("Rotating a point around the x axis", expected);
}

void test_inverse_rotation(void) {
	union Tuple point = new_point(0.0f, 1.0f, 0.0f);
	union Matrix4x4 halfQuarter = m4x4_rotation_x(M_PI / 4.0f);
	union Matrix4x4 inverse = m4x4_inverse(&halfQuarter);
	
	bool expected =
		eq_t(m4x4_mul_tuple(&inverse, &point), new_point(0.0f, sqrtf(2.0f) / 2.0f, -(sqrtf(2.0f) / 2.0f)));
	
	RESULT("The inverse of an x-rotation rotates in the opposite direction", expected);
}
