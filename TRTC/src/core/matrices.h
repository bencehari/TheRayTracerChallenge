#ifndef TRTC_MATRICES_H
#define TRTC_MATRICES_H

#include <stdbool.h>

#include "tuple.h"

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

// MATRICES
extern bool m4x4_eq(const union Matrix4x4* _m0, const union Matrix4x4* _m1);
extern bool m3x3_eq(const union Matrix3x3* _m0, const union Matrix3x3* _m1);
extern bool m2x2_eq(const union Matrix2x2* _m0, const union Matrix2x2* _m1);
extern union Matrix4x4 m4x4_mul(const union Matrix4x4* _m0, const union Matrix4x4* _m1);
extern union Tuple m4x4_mul_tuple(const union Matrix4x4* _m, const union Tuple* _t);
extern void m4x4_transpose(union Matrix4x4* _m);
extern float m2x2_determinant(const union Matrix2x2* _m);
extern union Matrix3x3 m4x4_submatrix(const union Matrix4x4* _m, int _row, int _col);
extern union Matrix2x2 m3x3_submatrix(const union Matrix3x3* _m, int _row, int _col);
extern float m3x3_minor(const union Matrix3x3* _m, int _row, int _col);
extern float m4x4_minor(const union Matrix4x4* _m, int _row, int _col);
extern float m3x3_cofactor(const union Matrix3x3* _m, int _row, int _col);
extern float m4x4_cofactor(const union Matrix4x4* _m, int _row, int _col);
extern float m3x3_determinant(const union Matrix3x3* _m);
extern float m4x4_determinant(const union Matrix4x4* _m);
extern bool m4x4_is_invertable(const union Matrix4x4* _m);
extern union Matrix4x4 m4x4_inverse(const union Matrix4x4* _m);
// TRANSFORMATIONS
extern union Matrix4x4 m4x4_translation(union Tuple _t);
extern union Matrix4x4 m4x4_scaling(union Tuple _t);
extern union Matrix4x4 m4x4_rotation_x(float _rad);
extern union Matrix4x4 m4x4_rotation_y(float _rad);
// DEBUG
extern void m4x4_print(const union Matrix4x4* _m);
extern void m3x3_print(const union Matrix3x3* _m);
extern void m2x2_print(const union Matrix2x2* _m);

#define m4x4_IDENTITY (union Matrix4x4) { .e = { [0] = 1.0f, [5] = 1.0f, [10] = 1.0f, [15] = 1.0f } }

#endif // TRTC_MATRICES_H
