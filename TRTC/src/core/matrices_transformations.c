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
