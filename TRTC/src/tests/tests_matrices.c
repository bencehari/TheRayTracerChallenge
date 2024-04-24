#include "tests.h"

#include <stdio.h>
#include <math.h>

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
void test_m4x4_is_invertable(void);
void test_m4x4_inverse(void);
void test_m4x4_inverse2(void);
void test_m4x4_inverse3(void);
void test_m4x4_inverse4(void);

void putting_it_together(void);

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
	test_m4x4_is_invertable();
	test_m4x4_inverse();
	test_m4x4_inverse2();
	test_m4x4_inverse3();
	test_m4x4_inverse4();
	
	putting_it_together();
}

// ~~~~~~~~~~~
// Utils
// ~~~~~~~~~~~

static const float EPSILON = 0.00001f;

static bool feq(float a, float b) {
	return fabs(a - b) < EPSILON;
}

static bool eq_m4(union Matrix4x4* _m0, union Matrix4x4* _m1) {
	return
		feq(_m0->e[ 0], _m1->e[ 0]) && feq(_m0->e[ 1], _m1->e[ 1]) &&
		feq(_m0->e[ 2], _m1->e[ 2]) && feq(_m0->e[ 3], _m1->e[ 3]) &&
		feq(_m0->e[ 4], _m1->e[ 4]) && feq(_m0->e[ 5], _m1->e[ 5]) &&
		feq(_m0->e[ 6], _m1->e[ 6]) && feq(_m0->e[ 7], _m1->e[ 7]) &&
		feq(_m0->e[ 8], _m1->e[ 8]) && feq(_m0->e[ 9], _m1->e[ 9]) &&
		feq(_m0->e[10], _m1->e[10]) && feq(_m0->e[11], _m1->e[11]) &&
		feq(_m0->e[12], _m1->e[12]) && feq(_m0->e[13], _m1->e[13]) &&
		feq(_m0->e[14], _m1->e[14]) && feq(_m0->e[15], _m1->e[15]);
}

// ~~~~~~~~~~~
// Tests
// ~~~~~~~~~~~

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

void test_m4x4_is_invertable(void) {
	union Matrix4x4 mInvertable = { .e = {
		6, 4, 4, 4,
		5, 5, 7, 6,
		4, -9, 3, -7,
		9, 1, 7, -6
	}};
	union Matrix4x4 mNotInvertable = { .e = {
		-4, 2, -2, -3,
		9, 6, 2, 6,
		0, -5, 1, -5,
		0, 0, 0, 0
	}};
	
	printf("Testing an invertible matrix for invertibility: %s\n", EVALUATE(m4x4_is_invertable(&mInvertable)));
	printf("Testing a noninvertible matrix for invertibility: %s\n", EVALUATE(!m4x4_is_invertable(&mNotInvertable)));
}

void test_m4x4_inverse(void) {
	union Matrix4x4 m = { .e = {
		-5, 2, 6, -8,
		1, -5, 1, 8,
		7, 7, -6, -7,
		1, -3, 7, 4
	}};
	union Matrix4x4 mInverse = m4x4_inverse(&m);
	
	float mDeterminant = m4x4_determinant(&m);
	float mCofactor = m4x4_cofactor(&m, 2, 3);
	float mCofactor2 = m4x4_cofactor(&m, 3, 2);

	bool expected =
		mDeterminant == 532.0f &&
		mCofactor == -160.0f &&
		mInverse.m[3][2] == mCofactor / mDeterminant &&
		mCofactor2 == 105.0f &&
		mInverse.m[2][3] == mCofactor2 / mDeterminant;
	
	printf("Calculating the inverse of a matrix: %s\n", EVALUATE(expected));
}

void test_m4x4_inverse2(void) {
	union Matrix4x4 m = { .e = {
		8, -5, 9, 2,
		7, 5, 6, 1,
		-6, 0, 9, 6,
		-3, 0, -9, -4
	}};
	union Matrix4x4 inverse = m4x4_inverse(&m);
	union Matrix4x4 expected = { .e = {
		-0.15385f, -0.15385f, -0.28205f, -0.53846f,
		-0.07692f, 0.12308f, 0.02564f, 0.03077f,
		0.35897f, 0.35897f, 0.43590f, 0.92308f,
		-0.69231, -0.69231, -0.76923, -1.92308
	}};
	
	// TODO: using m4x4_eq fails
	printf("Calculating the inverse of another matrix: %s\n", EVALUATE(eq_m4(&inverse, &expected)));
}

void test_m4x4_inverse3(void) {
	union Matrix4x4 m = { .e = {
		9, 3, 0, 9,
		-5, -2, -6, -3,
		-4, 9, 6, 4,
		-7, 6, 6, 2
	}};
	union Matrix4x4 inverse = m4x4_inverse(&m);
	union Matrix4x4 expected = { .e = {
		-0.04074f, -0.07778f, 0.14444f, -0.22222f,
		-0.07778f, 0.03333f, 0.36667f, -0.33333f,
		-0.02901f, -0.14630f, -0.10926f, 0.12963f,
		0.17778f, 0.06667f, -0.26667f, 0.33333
	}};
	
	// TODO: using m4x4_eq fails
	printf("Calculating the inverse of a third matrix: %s\n", EVALUATE(eq_m4(&inverse, &expected)));
}

void test_m4x4_inverse4(void) {
	union Matrix4x4 m = { .e = {
		3, -9, 7, 3,
		3, -8, 2, -9,
		-4, 4, 4, 1,
		-6, 5, -1, 1
	}};
	union Matrix4x4 m2 = { .e = {
		8, 2, 2, 2,
		3, -1, 7, 0,
		7, 0, 5, 4,
		6, -2, 0, 5
	}};
	
	union Matrix4x4 res = m4x4_mul(&m, &m2);
	union Matrix4x4 m2Inverse = m4x4_inverse(&m2);
	union Matrix4x4 reverse = m4x4_mul(&res, &m2Inverse);
	
	// TODO: using m4x4_eq fails
	printf("Multiplying a product by its inverse: %s\n", EVALUATE(eq_m4(&m, &reverse)));
}

void putting_it_together(void) {
	puts("What happens when you invert the identity matrix?");
	union Matrix4x4 identity = m4x4_IDENTITY;
	union Matrix4x4 invertedIdentity = m4x4_inverse(&identity);
	m4x4_print(&invertedIdentity);

	puts("\nWhat do you get when you multiply a matrix by its inverse?");
	union Matrix4x4 m = { .e = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	}};
	puts("Original:");
	m4x4_print(&m);
	
	union Matrix4x4 mInverse = m4x4_inverse(&m);
	union Matrix4x4 mMulByInverse = m4x4_mul(&m, &mInverse);
	puts("Multiplied by its inverse:");
	m4x4_print(&mMulByInverse);

	puts("\nIs there any difference between the inverse of the transpose of a matrix,\n"
	     "and the transpose of the inverse?");
	union Matrix4x4 m2 = { .e = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	}};
	puts("Original:");
	m4x4_print(&m2);
	
	m4x4_transpose(&m2);
	m2 = m4x4_inverse(&m2);
	puts("Inverse of transpose:");
	m4x4_print(&m2);
	
	m2 = (union Matrix4x4) { .e = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	}};
	m2 = m4x4_inverse(&m2);
	m4x4_transpose(&m2);
	puts("Transpose of inverse:");
	m4x4_print(&m2);

	puts("\nRemember how multiplying the identity matrix by a tuple gives you the tuple,\n"
	     "unchanged? Now, try changing any single element of the identity matrix to a\n"
	     "different number, and then multiplying it by a tuple. What happens to the tuple?");
	union Tuple t = new_point(4.0f, 3.0f, 2.0f);
	puts("Original tuple:");
	tuple_print(&t);
	
	identity.e[1] = 10.0f;
	puts("Modified identity matrix:");
	m4x4_print(&identity);
	
	t = m4x4_mul_tuple(&identity, &t);
	puts("Result:");
	tuple_print(&t);
}
