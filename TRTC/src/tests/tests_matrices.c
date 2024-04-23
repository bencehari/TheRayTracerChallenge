#include "tests.h"

#include <stdio.h>

#include "../core/matrices.h"
#include "../utils/consc.h"

#define EVALUATE(_expr) ((_expr) ? (AC_GREEN "PASS" AC_RESET) : (AC_RED "FAIL" AC_RESET))

void test_comp_same(void);
void test_comp_diff(void);
void test_multiply(void);
void test_identity(void);
void test_mul_w_identity(void);
void test_mul_identity_w_tuple(void);
void test_transpose(void);
void test_transpose_identity(void);
void test_m2x2_determinant(void);

void test_matrices(void) {
	puts(AC_YELLOW "Matrix4x4" AC_RESET);
	
	test_comp_same();
	test_comp_diff();
	test_multiply();
	test_identity();
	test_mul_w_identity();
	test_mul_identity_w_tuple();
	test_transpose();
	test_transpose_identity();
	test_m2x2_determinant();
}

void test_comp_same(void) {
	union Matrix4x4 m = { .e = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	}};
	union Matrix4x4 m1 = {{
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 },
		{ 13, 14, 15, 16 }
	}};
	
	printf("Compare same: %s\n", EVALUATE(m4x4_eq(&m, &m1)));
}

void test_comp_diff(void) {
	union Matrix4x4 m = { .e = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	}};
	union Matrix4x4 m2 = { .e = {
		2, 3, 4, 5,
		6, 7, 8, 9,
		10, 11, 12, 13,
		14, 15, 16, 17
	}};
	
	printf("Compare different: %s\n", EVALUATE(!m4x4_eq(&m, &m2)));
}

void test_multiply(void) {
	union Matrix4x4 mul = { .e = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 8, 7, 6,
		5, 4, 3, 2
	}};
	union Matrix4x4 mul1 = { .e = {
		-2, 1, 2, 3,
		3, 2, 1, -1,
		4, 3, 6, 5,
		1, 2, 7, 8
	}};
	union Matrix4x4 mulRes = { .e = {
		20, 22, 50, 48,
		44, 54, 114, 108,
		40, 58, 110, 102,
		16, 26, 46, 42
	}};
	
	union Matrix4x4 mulRet = m4x4_mul(&mul, &mul1);
	printf("Multiply: %s\n", EVALUATE(m4x4_eq(&mulRet, &mulRes)));
}

void test_identity(void) {
	union Matrix4x4 hmIdentity = { .e = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	}};
	union Matrix4x4 identity = m4x4_IDENTITY;
	
	printf("Identity matrix: %s\n", EVALUATE(m4x4_eq(&hmIdentity, &identity)));
}

void test_mul_w_identity(void) {
	union Matrix4x4 mulId = { .e = {
		0.0f, 1.0f, 2.0f, 4.0f,
		1.0f, 2.0f, 4.0f, 8.0f,
		2.0f, 4.0f, 8.0f, 16.0f,
		4.0f, 8.0f, 16.0f, 32.0f
	}};
	union Matrix4x4 identity = m4x4_IDENTITY;
	
	union Matrix4x4 mulIdRes = m4x4_mul(&mulId, &identity);
	
	printf("Multiplying a matrix by the identity matrix: %s\n", EVALUATE(m4x4_eq(&mulId, &mulIdRes)));
}

void test_mul_identity_w_tuple(void) {
	union Tuple tupleOrig = {{ 1.0f, 2.0f, 3.0f, 4.0f }};
	union Matrix4x4 identity = m4x4_IDENTITY;
	
	union Tuple mulM4x4TupleRes = m4x4_mul_tuple(&identity, &tupleOrig);
	printf("Multiplying the identity matrix by a tuple: %s\n", EVALUATE(tuple_eq(tupleOrig, mulM4x4TupleRes)));
}

void test_transpose(void) {
	union Matrix4x4 transposeOrig = { .e = {
		0, 9, 3, 0,
		9, 8, 0, 8,
		1, 8, 5, 3,
		0, 0, 5, 8
	}};
	union Matrix4x4 transposeExp = { .e = {
		0, 9, 1, 0,
		9, 8, 8, 0,
		3, 0, 5, 5,
		0, 8, 3, 8
	}};
	m4x4_transpose(&transposeOrig);
	
	printf("Transposing a matrix: %s\n", EVALUATE(m4x4_eq(&transposeOrig, &transposeExp)));
}

void test_transpose_identity(void) {
	union Matrix4x4 transpose = m4x4_IDENTITY;
	union Matrix4x4 identity = m4x4_IDENTITY;
	
	m4x4_transpose(&transpose);
	
	printf("Transposing the identity matrix: %s\n", EVALUATE(m4x4_eq(&transpose, &identity)));
}

void test_m2x2_determinant(void) {
	union Matrix2x2 m = { .e = { 1, 5, -3, 2 }};
	float determinant = m2x2_determinant(&m);
	printf("Calculating the determinant of a 2x2 matrix: %s\n", EVALUATE(determinant == 17.0f));
}
