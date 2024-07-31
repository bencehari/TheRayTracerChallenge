#include "matrices.h"

#include <stdio.h>

inline void m4x4_print(const union Matrix4x4* _m) {
	printf(
		"%.3f %.3f %.3f %.3f\n"
		"%.3f %.3f %.3f %.3f\n"
		"%.3f %.3f %.3f %.3f\n"
		"%.3f %.3f %.3f %.3f\n",
		_m->e[ 0], _m->e[ 1], _m->e[ 2], _m->e[ 3],
		_m->e[ 4], _m->e[ 5], _m->e[ 6], _m->e[ 7],
		_m->e[ 8], _m->e[ 9], _m->e[10], _m->e[11],
		_m->e[12], _m->e[13], _m->e[14], _m->e[15]);
}

inline void m3x3_print(const union Matrix3x3* _m) {
	printf(
		"%.3f %.3f %.3f\n"
		"%.3f %.3f %.3f\n"
		"%.3f %.3f %.3f\n",
		_m->e[ 0], _m->e[ 1], _m->e[ 2],
		_m->e[ 3], _m->e[ 4], _m->e[ 5],
		_m->e[ 6], _m->e[ 7], _m->e[ 8]);
}

inline void m2x2_print(const union Matrix2x2* _m) {
	printf(
		"%.3f %.3f\n"
		"%.3f %.3f\n",
		_m->e[ 0], _m->e[ 1],
		_m->e[ 2], _m->e[ 3]);
}
