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
void test_m4x4_submatrix(void);
void test_m3x3_submatrix(void);
void test_m3x3_minor(void);
void test_m3x3_cofactor(void);
void test_m3x3_determinant(void);
void test_m4x4_cofactor(void);
void test_m4x4_determinant(void);

void test_matrices(void) {
	puts(AC_YELLOW "Matrices" AC_RESET);
	
	test_comp_same();
	test_comp_diff();
	test_multiply();
	test_identity();
	test_mul_w_identity();
	test_mul_identity_w_tuple();
	test_transpose();
	test_transpose_identity();
	test_m2x2_determinant();
	test_m4x4_submatrix();
	test_m3x3_submatrix();
	test_m3x3_minor();
	test_m3x3_cofactor();
	test_m3x3_determinant();
	test_m4x4_cofactor();
	test_m4x4_determinant();
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

void test_m4x4_submatrix(void) {
	union Matrix4x4 m = { .e = {
		-6, 1, 1, 6,
		-8, 5, 8, 6,
		-1, 0, 8, 2,
		-7, 1, -1, 1
	}};
	union Matrix3x3 exp = { .e = {
		-6, 1, 6,
		-8, 8, 6,
		-7, -1, 1
	}};
	
	union Matrix3x3 res = m4x4_submatrix(&m, 2, 1);
	
	printf("A submatrix of a 4x4 matrix is a 3x3 matrix: %s\n", EVALUATE(m3x3_eq(&res, &exp)));
}

void test_m3x3_submatrix(void) {
	union Matrix3x3 m = { .e = {
		1, 5, 0,
		-3, 2, 7,
		0, 6, -3
	}};
	union Matrix2x2 exp = { .e = {
		-3, 2,
		0, 6
	}};
	
	union Matrix2x2 res = m3x3_submatrix(&m, 0, 2);
	
	printf("A submatrix of a 3x3 matrix is a 2x2 matrix: %s\n", EVALUATE(m2x2_eq(&res, &exp)));
}

void test_m3x3_minor(void) {
	union Matrix3x3 m = { .e = {
		3, 5, 0,
		2, -1, -7,
		6, -1, 5
	}};
	
	float minor = m3x3_minor(&m, 1, 0);
	
	printf("Calculating a minor of a 3x3 matrix: %s\n", EVALUATE(minor == 25.0f));
}

void test_m3x3_cofactor(void) {
	union Matrix3x3 m = { .e = {
		3, 5, 0,
		2, -1, -7,
		6, -1, 5
	}};
	
	float minorA = m3x3_minor(&m, 0, 0);
	float cofactorA = m3x3_cofactor(&m, 0, 0);
	float minorB = m3x3_minor(&m, 1, 0);
	float cofactorB = m3x3_cofactor(&m, 1, 0);
	
	/*printf(
		"minorA: %.1f, cofactorA: %.1f\nminorB: %.1f, cofactorB: %.1f\n",
		minorA, cofactorA, minorB, cofactorB);*/
	
	bool expected =
		minorA == -12.0f && cofactorA == -12.0f &&
		minorB == 25.0f && cofactorB == -25.0f;
	
	printf("Calculating a cofactor of a 3x3 matrix: %s\n", EVALUATE(expected));
}

void test_m3x3_determinant(void) {
	union Matrix3x3 m = { .e = {
		1, 2, 6,
		-5, 8, -4,
		2, 6, 4
	}};
	
	float cofactorA = m3x3_cofactor(&m, 0, 0);
	float cofactorB = m3x3_cofactor(&m, 0, 1);
	float cofactorC = m3x3_cofactor(&m, 0, 2);
	float determinant = m3x3_determinant(&m);
	
	/*printf(
		"%.1f %.1f %.1f %.1f\n",
		cofactorA, cofactorB, cofactorC, determinant);*/
	
	bool expected =
		cofactorA == 56.0f && cofactorB == 12.0f &&
		cofactorC == -46.0f && determinant == -196;
	
	printf("Calculating the determinant of a 3x3 matrix: %s\n", EVALUATE(expected));
}

void test_m4x4_cofactor(void) {
	union Matrix4x4 m = { .e = {
		-2, -8, 3, 5,
		-3, 1, 7, 3,
		1, 2, -9, 6,
		-6, 7, 7, -9
	}};
	
	float cofactorA = m4x4_cofactor(&m, 0, 0);
	float cofactorB = m4x4_cofactor(&m, 0, 1);
	float cofactorC = m4x4_cofactor(&m, 0, 2);
	float cofactorD = m4x4_cofactor(&m, 0, 3);
	
	/*printf(
		"%.1f %.1f %.1f %.1f\n",
		cofactorA, cofactorB, cofactorC, cofactorD);*/
	
	bool expected =
		cofactorA == 690.0f && cofactorB == 447.0f &&
		cofactorC == 210.0f && cofactorD == 51.0f;
	
	printf("Calculating the cofactors of a 4x4 matrix: %s\n", EVALUATE(expected));
}

void test_m4x4_determinant(void) {
	union Matrix4x4 m = { .e = {
		-2, -8, 3, 5,
		-3, 1, 7, 3,
		1, 2, -9, 6,
		-6, 7, 7, -9
	}};
	
	float cofactorA = m4x4_cofactor(&m, 0, 0);
	float cofactorB = m4x4_cofactor(&m, 0, 1);
	float cofactorC = m4x4_cofactor(&m, 0, 2);
	float cofactorD = m4x4_cofactor(&m, 0, 3);
	float determinant = m4x4_determinant(&m);
	
	bool expected =
		cofactorA == 690.0f && cofactorB == 447.0f &&
		cofactorC == 210.0f && cofactorD == 51.0f &&
		determinant == -4071;
	
	printf("Calculating the determinant of a 4x4 matrix: %s\n", EVALUATE(expected));
}
