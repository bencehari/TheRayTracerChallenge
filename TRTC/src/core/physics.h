#ifndef TRTC_PHYSICS_H
#define TRTC_PHYSICS_H

#include <stdio.h>

#include "tuple.h"
#include "ray.h"
#include "primitives.h"

enum Shape {
	SPHERE
};

static const char* shapeStr[] = {
	"Sphere"
};

struct Intersection {
	enum Shape shape;
	int objectId;
	struct Ray ray;
	int count;
	float times[2];
};

extern struct Intersection intersect_ray_sphere(struct Ray* _ray, struct Sphere* _sphere);

static const char* get_shape_name_by_enum(enum Shape _s) {
	return shapeStr[(int)_s];
}

static inline void intersection_print(struct Intersection* _i) {
	printf(
		"INTERSECTION\n"
		"Shape: %s (id: %d)\n",
		get_shape_name_by_enum(_i->shape),
		_i->objectId);
	ray_print(&_i->ray);
	printf(
		"Count: %d\nP1: %.3f\nP2: %.3f\n",
		_i->count, _i->times[0], _i->times[1]);
}

#endif // TRTC_PHYSICS_H
