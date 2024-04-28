#include "matrices.h"

#include <math.h>

#ifdef AD_CHK
	#include <stdlib.h> // exit
	#include "../utils/log.h"
#endif

inline union Matrix4x4 m4x4_translation(union Tuple _t) {
	return (union Matrix4x4) { .e = {
		[ 0] = 1.0f, [ 3] = _t.x,
		[ 5] = 1.0f, [ 7] = _t.y,
		[10] = 1.0f, [11] = _t.z,
		[15] = 1.0f
	}};
}

inline union Matrix4x4 m4x4_scaling(union Tuple _t) {
	return (union Matrix4x4) { .e = {
		[ 0] = _t.x, [ 5] = _t.y, [10] = _t.z, [15] = 1.0f
	}};
}

inline union Matrix4x4 m4x4_rotation_x(float _rad) {
	return (union Matrix4x4) { .e = {
		[ 0] = 1.0f,
		[ 5] = cosf(_rad), [ 6] = -sinf(_rad),
		[ 9] = sinf(_rad), [10] = cosf(_rad),
		[15] = 1.0f
	}};
}

inline union Matrix4x4 m4x4_rotation_y(float _rad) {
	return (union Matrix4x4) { .e = {
		[ 0] = cosf(_rad), [ 2] = sinf(_rad),
		[ 5] = 1.0f,
		[ 8] = -sinf(_rad), [10] = cosf(_rad),
		[15] = 1.0f
	}};
}

inline union Matrix4x4 m4x4_rotation_z(float _rad) {
	return (union Matrix4x4) { .e = {
		[ 0] = cosf(_rad), [ 1] = -sinf(_rad),
		[ 4] = sinf(_rad), [ 5] = cosf(_rad),
		[10] = 1.0f,
		[15] = 1.0f
	}};
}

inline union Matrix4x4 m4x4_shearing(float _xy, float _xz, float _yx, float _yz, float _zx, float _zy) {
	return (union Matrix4x4) { .e = {
		[ 0] = 1.0f, [ 1] = _xy, [ 2] = _xz,
		[ 4] = _yx, [ 5] = 1.0f, [ 6] = _yz,
		[ 8] = _zx, [ 9] = _zy, [10] = 1.0f,
		[15] = 1.0f
	}};
}
