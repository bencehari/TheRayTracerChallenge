#include "tests.h"

#include <stdio.h>
#include <math.h>

#include "../core/matrices.h"

// putting it together
#include "../core/render.h"
#include "../core/canvas.h"
#include "../core/color.h"
#include "../core/tuple.h"

void test_translation(void);
void test_inverse_translation(void);
void test_translate_vector(void);
void test_scale(void);
void test_scale_vector(void);
void test_inverse_scale(void);
void test_negative_scale(void);
void test_rotation_x(void);
void test_inverse_rotation_x(void);
void test_rotation_y(void);
void test_rotation_z(void);
void test_shearing(void);
void test_shearing_2(void);
void test_shearing_3(void);
void test_shearing_4(void);
void test_shearing_5(void);
void test_shearing_6(void);
void test_chain_transformations(void);
void test_chain_transformations_2(void);
void test_chain_transformations_3(void);

void transformations_putting_it_together(void);

void test_transformations(void) {
	test_translation();
	test_inverse_translation();
	test_translate_vector();
	test_scale();
	test_scale_vector();
	test_inverse_scale();
	test_negative_scale();
	test_rotation_x();
	test_inverse_rotation_x();
	test_rotation_y();
	test_rotation_z();
	test_shearing();
	test_shearing_2();
	test_shearing_3();
	test_shearing_4();
	test_shearing_5();
	test_shearing_6();
	test_chain_transformations();
	test_chain_transformations_2();
	test_chain_transformations_3();
	
	transformations_putting_it_together();
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
	union Matrix4x4 transform = m4x4_translation_t(new_point(5.0f, -3.0f, 2.0f));
	union Tuple point = new_point(-3.0f, 4.0f, 5.0f);
	union Tuple res = m4x4_mul_tuple(&transform, &point);
	
	RESULT("Multiplying by a translation matrix", tuple_eq(res, new_point(2.0f, 1.0f, 7.0f)));
}

void test_inverse_translation(void) {
	union Matrix4x4 transform = m4x4_translation_t(new_point(5.0f, -3.0f, 2.0f));
	union Matrix4x4 inverse = m4x4_inverse(&transform);
	union Tuple point = new_point(-3.0f, 4.0f, 5.0f);
	union Tuple res = m4x4_mul_tuple(&inverse, &point);
	
	RESULT("Multiplying by the inverse of a translation matrix", tuple_eq(res, new_point(-8.0f, 7.0f, 3.0f)));
}

void test_translate_vector(void) {
	union Matrix4x4 transform = m4x4_translation_t(new_point(5.0f, -3.0f, 2.0f));
	union Tuple vector = new_vector(-3.0f, 4.0f, 5.0f);
	union Tuple res = m4x4_mul_tuple(&transform, &vector);
	
	RESULT("A scaling matrix applied to a point", tuple_eq(res, vector));
}

void test_scale(void) {
	union Matrix4x4 transform = m4x4_scaling_t(new_point(2.0f, 3.0f, 4.0f));
	union Tuple point = new_point(-4.0f, 6.0f, 8.0f);
	union Tuple res = m4x4_mul_tuple(&transform, &point);
	
	RESULT("Translation does not affect vectors", tuple_eq(res, new_point(-8.0f, 18.0f, 32.0f)));
}

void test_scale_vector(void) {
	union Matrix4x4 transform = m4x4_scaling_t(new_point(2.0f, 3.0f, 4.0f));
	union Tuple vector = new_vector(-4.0f, 6.0f, 8.0f);
	union Tuple res = m4x4_mul_tuple(&transform, &vector);
	
	RESULT("A scaling matrix applied to a vector", tuple_eq(res, new_vector(-8.0f, 18.0f, 32.0f)));
}

void test_inverse_scale(void) {
	union Matrix4x4 transform = m4x4_scaling_t(new_point(2.0f, 3.0f, 4.0f));
	union Matrix4x4 inverse = m4x4_inverse(&transform);
	union Tuple vector = new_vector(-4.0f, 6.0f, 8.0f);
	union Tuple res = m4x4_mul_tuple(&inverse, &vector);
	
	RESULT("Multiplying by the inverse of a scaling matrix", tuple_eq(res, new_vector(-2.0f, 2.0f, 2.0f)));
}

void test_negative_scale(void) {
	union Matrix4x4 transform = m4x4_scaling_t(new_point(-1.0f, 1.0f, 1.0f));
	union Tuple point = new_point(2.0f, 3.0f, 4.0f);
	union Tuple res = m4x4_mul_tuple(&transform, &point);
	
	RESULT("Reflection is scaling by a negative value", tuple_eq(res, new_point(-2.0f, 3.0f, 4.0f)));
}

void test_rotation_x(void) {
	union Tuple point = new_point(0.0f, 1.0f, 0.0f);
	union Matrix4x4 halfQuarter = m4x4_rotation_x(M_PI / 4.0f);
	union Matrix4x4 fullQuarter = m4x4_rotation_x(M_PI / 2.0f);
	
	bool expected =
		eq_t(m4x4_mul_tuple(&halfQuarter, &point), new_point(0.0f, sqrtf(2.0f) / 2.0f, sqrtf(2.0f) / 2.0f)) &&
		eq_t(m4x4_mul_tuple(&fullQuarter, &point), new_point(0.0f, 0.0f, 1.0f));
	
	RESULT("Rotating a point around the x axis", expected);
}

void test_inverse_rotation_x(void) {
	union Tuple point = new_point(0.0f, 1.0f, 0.0f);
	union Matrix4x4 halfQuarter = m4x4_rotation_x(M_PI / 4.0f);
	union Matrix4x4 inverse = m4x4_inverse(&halfQuarter);
	
	bool expected =
		eq_t(m4x4_mul_tuple(&inverse, &point), new_point(0.0f, sqrtf(2.0f) / 2.0f, -(sqrtf(2.0f) / 2.0f)));
	
	RESULT("The inverse of an x-rotation rotates in the opposite direction", expected);
}

void test_rotation_y(void) {
	union Tuple point = new_point(0.0f, 0.0f, 1.0f);
	union Matrix4x4 halfQuarter = m4x4_rotation_y(M_PI / 4.0f);
	union Matrix4x4 fullQuarter = m4x4_rotation_y(M_PI / 2.0f);
	
	bool expected =
		eq_t(m4x4_mul_tuple(&halfQuarter, &point), new_point(sqrtf(2.0f) / 2.0f, 0.0f, sqrtf(2.0f) / 2.0f)) &&
		eq_t(m4x4_mul_tuple(&fullQuarter, &point), new_point(1.0f, 0.0f, 0.0f));
	
	RESULT("Rotating a point around the y axis", expected);
}

void test_rotation_z(void) {
	union Tuple point = new_point(0.0f, 1.0f, 0.0f);
	union Matrix4x4 halfQuarter = m4x4_rotation_z(M_PI / 4.0f);
	union Matrix4x4 fullQuarter = m4x4_rotation_z(M_PI / 2.0f);
	
	bool expected =
		eq_t(m4x4_mul_tuple(&halfQuarter, &point), new_point(-(sqrtf(2.0f) / 2.0f), sqrtf(2.0f) / 2.0f, 0.0f)) &&
		eq_t(m4x4_mul_tuple(&fullQuarter, &point), new_point(-1.0f, 0.0f, 0.0f));
	
	RESULT("Rotating a point around the z axis", expected);
}

void test_shearing(void) {
	union Matrix4x4 transform = m4x4_shearing(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	union Tuple point = new_point(2.0f, 3.0f, 4.0f);
	bool expected = tuple_eq(m4x4_mul_tuple(&transform, &point), new_point(5.0f, 3.0f, 4.0f));

	RESULT("A shearing transformation moves x in proportion to y", expected);
}

void test_shearing_2(void) {
	union Matrix4x4 transform = m4x4_shearing(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	union Tuple point = new_point(2.0f, 3.0f, 4.0f);
	bool expected = tuple_eq(m4x4_mul_tuple(&transform, &point), new_point(6.0f, 3.0f, 4.0f));

	RESULT("A shearing transformation moves x in proportion to z", expected); 
}

void test_shearing_3(void) {
	union Matrix4x4 transform = m4x4_shearing(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	union Tuple point = new_point(2.0f, 3.0f, 4.0f);
	bool expected = tuple_eq(m4x4_mul_tuple(&transform, &point), new_point(2.0f, 5.0f, 4.0f));

	RESULT("A shearing transformation moves y in proportion to x", expected);
}

void test_shearing_4(void) {
	union Matrix4x4 transform = m4x4_shearing(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	union Tuple point = new_point(2.0f, 3.0f, 4.0f);
	bool expected = tuple_eq(m4x4_mul_tuple(&transform, &point), new_point(2.0f, 7.0f, 4.0f));

	RESULT("A shearing transformation moves y in proportion to z", expected);
}

void test_shearing_5(void) {
	union Matrix4x4 transform = m4x4_shearing(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	union Tuple point = new_point(2.0f, 3.0f, 4.0f);
	bool expected = tuple_eq(m4x4_mul_tuple(&transform, &point), new_point(2.0f, 3.0f, 6.0f));

	RESULT("A shearing transformation moves z in proportion to x", expected);
}

void test_shearing_6(void) {
	union Matrix4x4 transform = m4x4_shearing(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	union Tuple point = new_point(2.0f, 3.0f, 4.0f);
	bool expected = tuple_eq(m4x4_mul_tuple(&transform, &point), new_point(2.0f, 3.0f, 7.0f));

	RESULT("A shearing transformation moves z in proportion to y", expected);
}

void test_chain_transformations(void) {
	union Tuple p = new_point(1.0f, 0.0f, 1.0f);
	union Matrix4x4 mRot = m4x4_rotation_x(M_PI * 0.5f);
	union Matrix4x4 mScale = m4x4_scaling(5.0f, 5.0f, 5.0f);
	union Matrix4x4 mTrans = m4x4_translation(10.f, 5.0f, 7.0f);
	
	union Tuple p2 = m4x4_mul_tuple(&mRot, &p);
	bool expected = eq_t(p2, new_point(1.0f, -1.0f, 0.0f));
	
	union Tuple p3 = m4x4_mul_tuple(&mScale, &p2);
	expected &= eq_t(p3, new_point(5.0f, -5.0f, 0.0f));
	
	union Tuple p4 = m4x4_mul_tuple(&mTrans, &p3);
	expected &= eq_t(p4, new_point(15.0f, 0.0f, 7.0f));
	
	RESULT("Individual transformations are applied in sequence", expected);
}

void test_chain_transformations_2(void) {
	union Tuple p = new_point(1.0f, 0.0f, 1.0f);
	union Matrix4x4 mRot = m4x4_rotation_x(M_PI * 0.5f);
	union Matrix4x4 mScale = m4x4_scaling(5.0f, 5.0f, 5.0f);
	union Matrix4x4 mTrans = m4x4_translation(10.f, 5.0f, 7.0f);
	
	union Matrix4x4 mTransScale = m4x4_mul(&mTrans, &mScale);
	union Matrix4x4 transform = m4x4_mul(&mTransScale, &mRot);
	bool expected = eq_t(m4x4_mul_tuple(&transform, &p), new_point(15.0f, 0.0f, 7.0f));
	
	RESULT("Chained transformations must be applied in reverse order", expected);
}

void test_chain_transformations_3(void) {
	union Tuple p = new_point(1.0f, 0.0f, 1.0f);
	union Matrix4x4 mRot = m4x4_rotation_x(M_PI * 0.5f);
	union Matrix4x4 mScale = m4x4_scaling(5.0f, 5.0f, 5.0f);
	union Matrix4x4 mTrans = m4x4_translation(10.f, 5.0f, 7.0f);
	
	union Matrix4x4 transform = m4x4_transform(&mTrans, &mScale, &mRot);
	bool expected = eq_t(m4x4_mul_tuple(&transform, &p), new_point(15.0f, 0.0f, 7.0f));
	
	RESULT("Chained transformations in one step", expected);
}

void transformations_putting_it_together(void) {
	const int width = 500;
	const int height = 500;
	
	canvas_initialize(width, height, COLOR_BLACK);
	
	if (render_init(width, height) != 0) {
		puts(AC_RED "Initializing render failed..." AC_RESET);
		return;
	}
	
	union Tuple dot = new_point(0.0f, 200.0f, 0.0f);
	const union Tuple screenCenter = new_point(width * 0.5f, height * 0.5f, 0.0f);
	const union Matrix4x4 mRot = m4x4_rotation_z(30.0f * (M_PI / 180.0f));
	
	for (int i = 0; i < 12; i++) {
		dot = m4x4_mul_tuple(&mRot, &dot);
		union Tuple finalPoint = tuple_add(screenCenter, dot);
		
		for (int j = -1; j < 2; j++) {
			for (int k = -1; k < 2; k++) {
				canvas_set_pixel(
					(int)finalPoint.x + j,
					(int)finalPoint.y + k,
					COLOR_RED);
			}
		}
	}
	
	uint32_t pixels[width * height];
	canvas_as_argb8888(pixels);
	canvas_cleanup();
	
	render_set_screen(pixels);
	
	render_cleanup();
}
