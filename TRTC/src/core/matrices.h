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

union Matrix3x3 {
	float m[3][3];
	float e[9];
};

union Matrix2x2 {
	float m[2][2];
	float e[4];
};

#define m4x4_IDENTITY (union Matrix4x4) { .e = { [0] = 1.0f, [5] = 1.0f, [10] = 1.0f, [15] = 1.0f } }

static inline bool m4x4_eq(const union Matrix4x4* _m0, const union Matrix4x4* _m1) {
	return
		_m0->e[ 0] == _m1->e[ 0] && _m0->e[ 1] == _m1->e[ 1] &&
		_m0->e[ 2] == _m1->e[ 2] && _m0->e[ 3] == _m1->e[ 3] &&
		_m0->e[ 4] == _m1->e[ 4] && _m0->e[ 5] == _m1->e[ 5] &&
		_m0->e[ 6] == _m1->e[ 6] && _m0->e[ 7] == _m1->e[ 7] &&
		_m0->e[ 8] == _m1->e[ 8] && _m0->e[ 9] == _m1->e[ 9] &&
		_m0->e[10] == _m1->e[10] && _m0->e[11] == _m1->e[11] &&
		_m0->e[12] == _m1->e[12] && _m0->e[13] == _m1->e[13] &&
		_m0->e[14] == _m1->e[14] && _m0->e[15] == _m1->e[15];
}

static inline bool m3x3_eq(const union Matrix3x3* _m0, const union Matrix3x3* _m1) {
	return
		_m0->e[0] == _m1->e[0] && _m0->e[1] == _m1->e[1] && _m0->e[2] == _m1->e[2] &&
		_m0->e[3] == _m1->e[3] && _m0->e[4] == _m1->e[4] && _m0->e[5] == _m1->e[5] &&
		_m0->e[6] == _m1->e[6] && _m0->e[7] == _m1->e[7] && _m0->e[8] == _m1->e[8];
}

static inline bool m2x2_eq(const union Matrix2x2* _m0, const union Matrix2x2* _m1) {
	return
		_m0->e[0] == _m1->e[0] && _m0->e[1] == _m1->e[1] &&
		_m0->e[2] == _m1->e[2] && _m0->e[3] == _m1->e[3];
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
		_m->e[ 0] * _t->x + _m->e[ 1] * _t->x + _m->e[ 2] * _t->x + _m->e[ 3] * _t->x,
		_m->e[ 4] * _t->y + _m->e[ 5] * _t->y + _m->e[ 6] * _t->y + _m->e[ 7] * _t->y,
		_m->e[ 8] * _t->z + _m->e[ 9] * _t->z + _m->e[10] * _t->z + _m->e[11] * _t->z,
		_m->e[12] * _t->w + _m->e[13] * _t->w + _m->e[14] * _t->w + _m->e[15] * _t->w
	}};
}

static inline void m4x4_transpose(union Matrix4x4* _m) {
	*_m = (union Matrix4x4) {{
		{ _m->e[ 0], _m->e[ 4], _m->e[ 8], _m->e[12] },
		{ _m->e[ 1], _m->e[ 5], _m->e[ 9], _m->e[13] },
		{ _m->e[ 2], _m->e[ 6], _m->e[10], _m->e[14] },
		{ _m->e[ 3], _m->e[ 7], _m->e[11], _m->e[15] }
	}};
}

static inline float m2x2_determinant(const union Matrix2x2* _m) {
	return _m->e[0] * _m->e[3] - _m->e[1] * _m->e[2];
}

static inline union Matrix3x3 m4x4_submatrix(const union Matrix4x4* _m, int _row, int _col) {
	union Matrix3x3 ret;
	for (int r = 0, i = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (r == _row || c == _col) continue;
			ret.e[i++] = _m->m[r][c];
		}
	}
	return ret;
}

static inline union Matrix2x2 m3x3_submatrix(const union Matrix3x3* _m, int _row, int _col) {
	union Matrix2x2 ret;
	for (int r = 0, i = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (r == _row || c == _col) continue;
			ret.e[i++] = _m->m[r][c];
		}
	}
	return ret;
}

static inline float m3x3_minor(const union Matrix3x3* _m, int _row, int _col) {
	union Matrix2x2 subm = m3x3_submatrix(_m, _row, _col);
	return m2x2_determinant(&subm);
}

static inline float m3x3_cofactor(const union Matrix3x3* _m, int _row, int _col) {
	return m3x3_minor(_m, _row, _col) * ((_row + _col) % 2 != 0 ? -1 : 1);
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
