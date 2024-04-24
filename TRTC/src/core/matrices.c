#include "matrices.h"

#ifdef AD_CHK
	#include <stdlib.h> // exit
	#include "../utils/log.h"
#endif

inline bool m4x4_eq(const union Matrix4x4* _m0, const union Matrix4x4* _m1) {
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

inline bool m3x3_eq(const union Matrix3x3* _m0, const union Matrix3x3* _m1) {
	return
		_m0->e[0] == _m1->e[0] && _m0->e[1] == _m1->e[1] && _m0->e[2] == _m1->e[2] &&
		_m0->e[3] == _m1->e[3] && _m0->e[4] == _m1->e[4] && _m0->e[5] == _m1->e[5] &&
		_m0->e[6] == _m1->e[6] && _m0->e[7] == _m1->e[7] && _m0->e[8] == _m1->e[8];
}

inline bool m2x2_eq(const union Matrix2x2* _m0, const union Matrix2x2* _m1) {
	return
		_m0->e[0] == _m1->e[0] && _m0->e[1] == _m1->e[1] &&
		_m0->e[2] == _m1->e[2] && _m0->e[3] == _m1->e[3];
}

inline union Matrix4x4 m4x4_mul(const union Matrix4x4* _m0, const union Matrix4x4* _m1) {
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

inline union Tuple m4x4_mul_tuple(const union Matrix4x4* _m, const union Tuple* _t) {
	return (union Tuple) {{
		_m->e[ 0] * _t->x + _m->e[ 1] * _t->y + _m->e[ 2] * _t->z + _m->e[ 3] * _t->w,
		_m->e[ 4] * _t->x + _m->e[ 5] * _t->y + _m->e[ 6] * _t->z + _m->e[ 7] * _t->w,
		_m->e[ 8] * _t->x + _m->e[ 9] * _t->y + _m->e[10] * _t->z + _m->e[11] * _t->w,
		_m->e[12] * _t->x + _m->e[13] * _t->y + _m->e[14] * _t->z + _m->e[15] * _t->w
	}};
}

inline void m4x4_transpose(union Matrix4x4* _m) {
	*_m = (union Matrix4x4) {{
		{ _m->e[ 0], _m->e[ 4], _m->e[ 8], _m->e[12] },
		{ _m->e[ 1], _m->e[ 5], _m->e[ 9], _m->e[13] },
		{ _m->e[ 2], _m->e[ 6], _m->e[10], _m->e[14] },
		{ _m->e[ 3], _m->e[ 7], _m->e[11], _m->e[15] }
	}};
}

inline float m2x2_determinant(const union Matrix2x2* _m) {
	return _m->e[0] * _m->e[3] - _m->e[1] * _m->e[2];
}

inline union Matrix3x3 m4x4_submatrix(const union Matrix4x4* _m, int _row, int _col) {
#ifdef AD_CHK
	if (_row < 0 || _row > 3 || _col < 0 || _row > 3) {
		LOG_E("m4x4_submatrix: _row or _col out of bounds!");
		exit(0);
	}
#endif // AD_CHK
	
	union Matrix3x3 ret;
	for (int r = 0, i = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (r == _row || c == _col) continue;
			ret.e[i++] = _m->m[r][c];
		}
	}
	return ret;
}

inline union Matrix2x2 m3x3_submatrix(const union Matrix3x3* _m, int _row, int _col) {
#ifdef AD_CHK
	if (_row < 0 || _row > 2 || _col < 0 || _row > 2) {
		LOG_E("m3x3_submatrix: _row or _col out of bounds!");
		exit(0);
	}
#endif // AD_CHK
	
	union Matrix2x2 ret;
	for (int r = 0, i = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (r == _row || c == _col) continue;
			ret.e[i++] = _m->m[r][c];
		}
	}
	return ret;
}

inline float m3x3_minor(const union Matrix3x3* _m, int _row, int _col) {
#ifdef AD_CHK
	if (_row < 0 || _row > 2 || _col < 0 || _row > 2) {
		LOG_E("m3x3_minor: _row or _col out of bounds!");
		exit(0);
	}
#endif // AD_CHK
	
	union Matrix2x2 subm = m3x3_submatrix(_m, _row, _col);
	return m2x2_determinant(&subm);
}

inline float m4x4_minor(const union Matrix4x4* _m, int _row, int _col) {
#ifdef AD_CHK
	if (_row < 0 || _row > 3 || _col < 0 || _row > 3) {
		LOG_E("m4x4_minor: _row or _col out of bounds!");
		exit(0);
	}
#endif // AD_CHK	

	union Matrix3x3 subm = m4x4_submatrix(_m, _row, _col);
	return m3x3_determinant(&subm);
}

inline float m3x3_cofactor(const union Matrix3x3* _m, int _row, int _col) {
#ifdef AD_CHK
	if (_row < 0 || _row > 2 || _col < 0 || _row > 2) {
		LOG_E("m3x3_cofactor: _row or _col out of bounds!");
		exit(0);
	}
#endif // AD_CHK
	
	return m3x3_minor(_m, _row, _col) * ((_row + _col) % 2 != 0 ? -1 : 1);
}

inline float m4x4_cofactor(const union Matrix4x4* _m, int _row, int _col) {
#ifdef AD_CHK
	if (_row < 0 || _row > 3 || _col < 0 || _row > 3) {
		LOG_E("m4x4_cofactor: _row or _col out of bounds!");
		exit(0);
	}
#endif // AD_CHK
	
	return m4x4_minor(_m, _row, _col) * ((_row + _col) % 2 != 0 ? -1 : 1);
}

inline float m3x3_determinant(const union Matrix3x3* _m) {
	float ret = 0;
	for (int i = 0; i < 3; i++) {
		ret += _m->m[0][i] * m3x3_cofactor(_m, 0, i);
	}
	return ret;
}

inline float m4x4_determinant(const union Matrix4x4* _m) {
	float ret = 0;
	for (int i = 0; i < 4; i++) {
		ret += _m->m[0][i] * m4x4_cofactor(_m, 0, i);
	}
	return ret;
}

inline bool m4x4_is_invertable(const union Matrix4x4* _m) {
	return m4x4_determinant(_m) != 0.0f;
}

inline union Matrix4x4 m4x4_inverse(const union Matrix4x4* _m) {
	float determinant = m4x4_determinant(_m);
	
	union Matrix4x4 inverse;
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			inverse.m[r][c] = m4x4_cofactor(_m, r, c) / determinant;
		}
	}
	
	m4x4_transpose(&inverse);
	
	return inverse;
}
