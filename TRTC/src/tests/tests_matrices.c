#include "tests.h"

#include <stdio.h>

#include "../core/matrices.h"
#include "../utils/consc.h"

#define EVALUATE(_expr) ((_expr) ? (AC_GREEN "PASS" AC_RESET) : (AC_RED "FAIL" AC_RESET))

void test_matrices(void) {
	puts(AC_YELLOW "Matrix4x4" AC_RESET);
	
	union Matrix4x4 m = {
		.e = {
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12,
			13, 14, 15, 16
		}
	};
	union Matrix4x4 m1 = {{
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 },
		{ 13, 14, 15, 16 }
	}};
	
	printf("Compare same: %s\n", EVALUATE(m4x4_eq(&m, &m1)));

	union Matrix4x4 m2 = {
		.e = {
			2, 3, 4, 5,
			6, 7, 8, 9,
			10, 11, 12, 13,
			14, 15, 16, 17
		}
	};
	
	printf("Compare different: %s\n", EVALUATE(!m4x4_eq(&m, &m2)));
	
	union Matrix4x4 mul = {
		.e = {
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		}
	};
	union Matrix4x4 mul1 = {
		.e = {
			-2, 1, 2, 3,
			3, 2, 1, -1,
			4, 3, 6, 5,
			1, 2, 7, 8
		}
	};
	union Matrix4x4 mulRes = {
		.e = {
			20, 22, 50, 48,
			44, 54, 114, 108,
			40, 58, 110, 102,
			16, 26, 46, 42
		}
	};
	
	union Matrix4x4 mulRet = m4x4_mul(&mul, &mul1);
	printf("Multiply: %s\n", EVALUATE(m4x4_eq(&mulRet, &mulRes)));
	
	union Matrix4x4 hmIdentity = {
		.e = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		}
	};
	union Matrix4x4 identity = m4x4_IDENTITY;
	
	printf("Identity matrix: %s\n", EVALUATE(m4x4_eq(&hmIdentity, &identity)));
	
	union Matrix4x4 mulId = {
		.e = {
			0.0f, 1.0f, 2.0f, 4.0f,
			1.0f, 2.0f, 4.0f, 8.0f,
			2.0f, 4.0f, 8.0f, 16.0f,
			4.0f, 8.0f, 16.0f, 32.0f
		}
	};
	union Matrix4x4 mulIdRes = m4x4_mul(&mulId, &hmIdentity);
	
	printf("Multiplying a matrix by the identity matrix: %s\n", EVALUATE(m4x4_eq(&mulId, &mulIdRes)));
	
	union Tuple tupleOrig = (union Tuple) {{ 1.0f, 2.0f, 3.0f, 4.0f }};
	
	union Tuple mulM4x4TupleRes = m4x4_mul_tuple(&hmIdentity, &tupleOrig);
	printf("Multiplying the identity matrix by a tuple: %s\n", EVALUATE(tuple_eq(tupleOrig, mulM4x4TupleRes)));
	
	union Matrix4x4 transposeOrig = (union Matrix4x4) {
		.e = {
			0, 9, 3, 0,
			9, 8, 0, 8,
			1, 8, 5, 3,
			0, 0, 5, 8
		}
	};
	union Matrix4x4 transposeExp = (union Matrix4x4) {
		.e = {
			0, 9, 1, 0,
			9, 8, 8, 0,
			3, 0, 5, 5,
			0, 8, 3, 8
		}
	};
	m4x4_transpose(&transposeOrig);
	
	printf("Transposing a matrix: %s\n", EVALUATE(m4x4_eq(&transposeOrig, &transposeExp)));
	
	m4x4_transpose(&hmIdentity);
	
	printf("Transposing the identity matrix: %s\n", EVALUATE(m4x4_eq(&hmIdentity, &identity)));
}
