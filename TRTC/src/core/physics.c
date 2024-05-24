#include "physics.h"

struct Intersection intersect_ray_sphere(struct Ray* _ray, struct Sphere* _sphere) {
	struct Intersection ret = { .shape = SPHERE, .objectId = _sphere->id };
	
	return ret;
}
