#ifndef TRTC_PRIMITIVES_H
#define TRTC_PRIMITIVES_H

#include "tuple.h"

/**
 * @brief Create with new_sphere() function!
 */
struct Sphere {
	int id;
	union Tuple pos;
	float radus;
};

extern struct Sphere new_sphere();

#endif // TRTC_PRIMITIVES_H
