#include "tests.h"

#include "../core/ray.h"
#include "../core/tuple.h"

void test_create_ray(void);
void test_compute_point_from_distance(void);
void test_translating_ray(void);
void test_scaling_ray(void);

void test_ray_sphere_intersections(void) {
	test_create_ray();
	test_compute_point_from_distance();
	test_translating_ray();
	test_scaling_ray();
}

// ~~~~~~~~~~~
// Utils
// ~~~~~~~~~~~

static const float EPSILON = 0.00001f;

static bool feq(float a, float b) {
	return fabs(a - b) < EPSILON;
}

static bool eq_t(const union Tuple _t0, const union Tuple _t1) {
	return
		feq(_t0.e[ 0], _t1.e[ 0]) &&
		feq(_t0.e[ 1], _t1.e[ 1]) &&
		feq(_t0.e[ 2], _t1.e[ 2]);
}

// ~~~~~~~~~~~
// Tests
// ~~~~~~~~~~~

void test_create_ray(void) {
	union Tuple origin = new_point(1.0f, 2.0f, 3.0f);
	union Tuple direction = new_vector(4.0f, 5.0f, 6.0f);
	
	struct Ray ray = new_ray(origin, direction);
	
	RESULT("Creating and querying a ray", tuple_eq(origin, ray.origin) && tuple_eq(direction, ray.dir));
}

void test_compute_point_from_distance(void) {
	struct Ray ray = new_ray(new_point(2.0f, 3.0f, 4.0f), new_vector(1.0f, 0.0f, 0.0f));
	
	RESULT("Computing a point from a distance",
		tuple_eq(ray_position(&ray, 0.0f), new_point(2.0f, 3.0f, 4.0f)) &&
		tuple_eq(ray_position(&ray, 1.0f), new_point(3.0f, 3.0f, 4.0f)) &&
		tuple_eq(ray_position(&ray, -1.0f), new_point(1.0f, 3.0f, 4.0f)) &&
		tuple_eq(ray_position(&ray, 2.5f), new_point(4.5f, 3.0f, 4.0f)));
}

void test_translating_ray(void) {
	
}

void test_scaling_ray(void) {
	
}
