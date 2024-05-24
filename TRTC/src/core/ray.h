#ifndef TRTC_RAY_H
#define TRTC_RAY_H

#include "tuple.h"

#if AD_CHK
	#include "../utils/log.h"
#endif

struct Ray {
	union Tuple origin;
	union Tuple dir;
};

static inline struct Ray new_ray(union Tuple _origin, union Tuple _direction) {
#if AD_CHK
	if (!tuple_is_point(&_origin)) LOG_W("new_ray: _origin is not a point!");
	if (!tuple_is_vector(&_direction)) LOG_W("new_ray: _direction is not a vector!");
#endif
	
	return (struct Ray) {
		.origin = _origin,
		.dir = _direction
	};
}

static inline union Tuple ray_position(struct Ray* _ray, float _t) {
	return tuple_add(_ray->origin, tuple_mul_f(_ray->dir, _t));
}

static inline void ray_print(struct Ray* _ray) {
	printf("RAY\norigin: ");
	tuple_print(&_ray->origin);
	printf("dir: ");
	tuple_print(&_ray->dir);
}

#endif // TRTC_RAY_H
