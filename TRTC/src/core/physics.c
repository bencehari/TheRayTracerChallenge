#include "physics.h"

#include <math.h>
#include <stdio.h>
#include <float.h>

struct Intersection intersect_ray_sphere(struct Ray* _ray, struct Sphere* _sphere) {
	struct Intersection ret = {
		.shape = SPHERE,
		.objectId = _sphere->id,
		.ray = _ray
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

struct Hit get_hit_from_intersections(const struct Intersection* _intersections, const int _count) {
	struct Hit hit = { .intersection = NULL, .index = -1 };
	
	float best = FLT_MAX;
	for (int i = 0; i < _count; i++) {
		struct Intersection* is = (struct Intersection*)&_intersections[i];
		if (is->count == 0) continue;

		if (is->times[0] >= 0 && is->times[0] < best) {
			hit.intersection = is;
			hit.index = 0;
			best = is->times[0];
		}
		if (is->times[1] >= 0 && is->times[1] < best) {
			hit.intersection = is;
			hit.index = 1;
			best = is->times[1];
		}
	}
	
	return hit;
}
