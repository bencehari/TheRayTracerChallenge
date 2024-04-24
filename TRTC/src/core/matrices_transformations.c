#include "matrices.h"

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
