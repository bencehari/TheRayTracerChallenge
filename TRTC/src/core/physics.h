#ifndef TRTC_PHYSICS_H
#define TRTC_PHYSICS_H

#include "tuple.h"
#include "ray.h"
#include "primitives.h"

enum Shape {
	SPHERE
};

struct Intersection {
	enum Shape shape;
	int objectId;
	struct Ray ray;
	int count;
	float* times;
};

extern struct Intersection intersect_ray_sphere(struct Ray* _ray, struct Sphere* _sphere);

#endif // TRTC_PHYSICS_H
