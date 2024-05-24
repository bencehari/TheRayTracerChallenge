#include "physics.h"

#include <math.h>
#include <stdio.h>

struct Intersection intersect_ray_sphere(struct Ray* _ray, struct Sphere* _sphere) {
	struct Intersection ret = {
		.shape = SPHERE,
		.objectId = _sphere->id,
		.ray = *_ray
	};

	union Tuple sphereToRay = tuple_sub(_ray->origin, _sphere->pos);
	
	float a = tuple_dot(_ray->dir, _ray->dir);
	float b = 2.0f * tuple_dot(_ray->dir, sphereToRay);
	float c = tuple_dot(sphereToRay, sphereToRay) - 1.0f;
	
	float discriminant = powf(b, 2.0f) - 4.0f * a * c;

	if (discriminant < 0) return ret;

	ret.times[0] = (-b - sqrtf(discriminant)) / (2 * a);
	ret.times[1] = (-b + sqrtf(discriminant)) / (2 * a);
	
	// ret.count = ret.times[0] == ret.times[1] ? 1 : 2;
	ret.count = 2;
	
	return ret;
}
