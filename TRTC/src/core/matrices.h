#ifndef TRTC_MATRICES_H
#define TRTC_MATRICES_H

#include <stdio.h>
#include <stdbool.h>

#include "tuple.h"

#ifdef AD_CHK
	#include <stdlib.h> // exit
	#include "../utils/log.h"
#endif

union Matrix4x4 {
	float m[4][4];
	float e[16];
};

#define m4x4_IDENTITY (union Matrix4x4) { .e = { [0] = 1.0f, [5] = 1.0f, [10] = 1.0f, [15] = 1.0f } }

static inline bool m4x4_eq(const union Matrix4x4* _m0, const union Matrix4x4* _m1) {
	return
		_m0->m[0][0] == _m1->m[0][0] && _m0->m[0][1] == _m1->m[0][1] &&
		_m0->m[0][2] == _m1->m[0][2] && _m0->m[0][3] == _m1->m[0][3] &&
		_m0->m[1][0] == _m1->m[1][0] && _m0->m[1][1] == _m1->m[1][1] &&
		_m0->m[1][2] == _m1->m[1][2] && _m0->m[1][3] == _m1->m[1][3] &&
		_m0->m[2][0] == _m1->m[2][0] && _m0->m[2][1] == _m1->m[2][1] &&
		_m0->m[2][2] == _m1->m[2][2] && _m0->m[2][3] == _m1->m[2][3] &&
		_m0->m[3][0] == _m1->m[3][0] && _m0->m[3][1] == _m1->m[3][1] &&
		_m0->m[3][2] == _m1->m[3][2] && _m0->m[3][3] == _m1->m[3][3];
}

static inline union Matrix4x4 m4x4_mul(const union Matrix4x4* _m0, const union Matrix4x4* _m1) {
	union Matrix4x4 ret;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			ret.m[row][col] =
				_m0->m[row][0] * _m1->m[0][col] +
				_m0->m[row][1] * _m1->m[1][col] +
				_m0->m[row][2] * _m1->m[2][col] +
				_m0->m[row][3] * _m1->m[3][col];
		}
	}
	return ret;
}

static inline union Tuple m4x4_mul_tuple(const union Matrix4x4* _m, const union Tuple* _t) {
	return (union Tuple) {{
		_m->m[0][0] * _t->x + _m->m[0][1] * _t->x + _m->m[0][2] * _t->x + _m->m[0][3] * _t->x,
		_m->m[1][0] * _t->y + _m->m[1][1] * _t->y + _m->m[1][2] * _t->y + _m->m[1][3] * _t->y,
		_m->m[2][0] * _t->z + _m->m[2][1] * _t->z + _m->m[2][2] * _t->z + _m->m[2][3] * _t->z,
		_m->m[3][0] * _t->w + _m->m[3][1] * _t->w + _m->m[3][2] * _t->w + _m->m[3][3] * _t->w
	}};
}

static inline void m4x4_print(const union Matrix4x4* _m) {
	printf(
		"%.3f %.3f %.3f %.3f\n"
		"%.3f %.3f %.3f %.3f\n"
		"%.3f %.3f %.3f %.3f\n"
		"%.3f %.3f %.3f %.3f\n",
		_m->m[0][0], _m->m[0][1], _m->m[0][2], _m->m[0][3],
		_m->m[1][0], _m->m[1][1], _m->m[1][2], _m->m[1][3],
		_m->m[2][0], _m->m[2][1], _m->m[2][2], _m->m[2][3],
		_m->m[3][0], _m->m[3][1], _m->m[3][2], _m->m[3][3]);
}

#endif // TRTC_MATRICES_H
