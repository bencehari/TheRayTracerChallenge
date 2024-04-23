#include "tests.h"

#include <stdio.h>

#include "../core/matrices.h"
#include "../utils/consc.h"

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
	
	printf("Compare same: %s\n", m4x4_eq(&m, &m1) ? (AC_GREEN "PASS" AC_RESET) : (AC_RED "FAIL" AC_RESET));

	union Matrix4x4 m2 = {
		.e = {
			2, 3, 4, 5,
			6, 7, 8, 9,
			10, 11, 12, 13,
			14, 15, 16, 17
		}
	};
	
	printf("Compare different: %s\n", !m4x4_eq(&m, &m2) ? (AC_GREEN "PASS" AC_RESET) : (AC_RED "FAIL" AC_RESET));
	
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
	printf("Multiply: %s\n", m4x4_eq(&mulRet, &mulRes) ? (AC_GREEN "PASS" AC_RESET) : (AC_RED "FAIL" AC_RESET));
}
