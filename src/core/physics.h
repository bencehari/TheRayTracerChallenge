#ifndef TRTC_PHYSICS_H
#define TRTC_PHYSICS_H

#include <stdio.h>
#include <stdbool.h>

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
	struct Ray* ray;
	int count;
	float times[2];
};

struct Hit {
	struct Intersection* intersection;
	int index;
};

extern struct Intersection intersect_ray_sphere(struct Ray* _ray, struct Sphere* _sphere);

extern struct Hit get_hit_from_intersections(const struct Intersection* _intersections, const int _count);

static const char* get_shape_name_by_enum(enum Shape _s) {
	return shapeStr[(int)_s];
}

static inline bool hit_is_valid(struct Hit* _hit) {
	return _hit->intersection != NULL && _hit->index > -1;
}

static inline void intersection_print(struct Intersection* _i) {
	printf(
		"INTERSECTION\n"
		"Shape: %s (id: %d)\n",
		get_shape_name_by_enum(_i->shape),
		_i->objectId);
	ray_print(_i->ray);
	printf(
		"Count: %d\nP1: %.3f\nP2: %.3f\n",
		_i->count, _i->times[0], _i->times[1]);
}

static inline void hit_print(struct Hit* _hit) {
	printf(
		"HIT\nIntersection: %s\nIndex: %d\n",
		_hit->intersection == NULL ? "false" : "true", _hit->index);
}

#endif // TRTC_PHYSICS_H
