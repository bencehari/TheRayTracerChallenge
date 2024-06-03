#ifndef TRTC_RAY_H
#define TRTC_RAY_H

#include "tuple.h"
#include "matrices.h"

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

static inline struct Ray ray_transform(struct Ray* _ray, union Matrix4x4* _m) {
	return (struct Ray) {
		.origin = m4x4_mul_tuple(_m, &_ray->origin),
		.dir = m4x4_mul_tuple(_m, &_ray->dir)
	};
}

static inline void ray_print(struct Ray* _ray) {
	printf("RAY\norigin: ");
	tuple_print(&_ray->origin);
	printf("dir: ");
	tuple_print(&_ray->dir);
}

#endif // TRTC_RAY_H
