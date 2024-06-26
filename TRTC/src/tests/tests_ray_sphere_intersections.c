#include "tests.h"

#include "../core/ray.h"
#include "../core/tuple.h"
#include "../core/physics.h"

void test_create_ray(void);
void test_compute_point_from_distance(void);
void test_ray_intersects_sphere(void);
void test_ray_intersects_sphere_at_tangent(void);
void test_ray_misses_sphere(void);
void test_ray_originates_inside_sphere(void);
void test_intersection_hit_1(void);
void test_intersection_hit_2(void);
void test_intersection_hit_3(void);
void test_intersection_hit_4(void);
void test_translating_ray(void);
void test_scaling_ray(void);

void test_ray_sphere_intersections(void) {
	test_create_ray();
	test_compute_point_from_distance();
	test_ray_intersects_sphere();
	test_ray_intersects_sphere_at_tangent();
	test_ray_misses_sphere();
	test_ray_originates_inside_sphere();
	test_intersection_hit_1();
	test_intersection_hit_2();
	test_intersection_hit_3();
	test_intersection_hit_4();
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

void test_ray_intersects_sphere(void) {
	union Tuple origin = new_point(0.0f, 0.0f, -5.0f);
	union Tuple direction = new_vector(0.0f, 0.0f, 1.0f);
	
	struct Ray ray = new_ray(origin, direction);
	struct Sphere sphere = new_sphere();
	
	struct Intersection intersection = intersect_ray_sphere(&ray, &sphere);
	// intersection_print(&intersection);
	
	bool expected =
		intersection.shape == SPHERE &&
		intersection.count == 2 &&
		intersection.times[0] == 4.0f &&
		intersection.times[1] == 6.0f;
	
	RESULT("A ray intersects a sphere at two points", expected);
}

void test_ray_intersects_sphere_at_tangent(void) {
	union Tuple origin = new_point(0.0f, 1.0f, -5.0f);
	union Tuple direction = new_vector(0.0f, 0.0f, 1.0f);
	
	struct Ray ray = new_ray(origin, direction);
	struct Sphere sphere = new_sphere();
	
	struct Intersection intersection = intersect_ray_sphere(&ray, &sphere);
	// intersection_print(&intersection);
	
	bool expected =
		intersection.shape == SPHERE &&
		intersection.count == 2 &&
		intersection.times[0] == 5.0f &&
		intersection.times[1] == 5.0f;
	
	RESULT("A ray intersects a sphere at a tangent", expected);
}

void test_ray_misses_sphere(void) {
	union Tuple origin = new_point(0.0f, 2.0f, -5.0f);
	union Tuple direction = new_vector(0.0f, 0.0f, 1.0f);
	
	struct Ray ray = new_ray(origin, direction);
	struct Sphere sphere = new_sphere();
	
	struct Intersection intersection = intersect_ray_sphere(&ray, &sphere);
	// intersection_print(&intersection);
	
	bool expected =
		intersection.shape == SPHERE &&
		intersection.count == 0;
	
	RESULT("A ray misses a sphere", expected);
}

void test_ray_originates_inside_sphere(void) {
	union Tuple origin = new_point(0.0f, 0.0f, 0.0f);
	union Tuple direction = new_vector(0.0f, 0.0f, 1.0f);
	
	struct Ray ray = new_ray(origin, direction);
	struct Sphere sphere = new_sphere();
	
	struct Intersection intersection = intersect_ray_sphere(&ray, &sphere);
	// intersection_print(&intersection);
	
	bool expected =
		intersection.shape == SPHERE &&
		intersection.count == 2 &&
		intersection.times[0] == -1.0f &&
		intersection.times[1] == 1.0f;
	
	RESULT("A ray originates inside a sphere", expected);
}

void test_sphere_behind_ray(void) {
	union Tuple origin = new_point(0.0f, 0.0f, 5.0f);
	union Tuple direction = new_vector(0.0f, 0.0f, 1.0f);
	
	struct Ray ray = new_ray(origin, direction);
	struct Sphere sphere = new_sphere();
	
	struct Intersection intersection = intersect_ray_sphere(&ray, &sphere);
	// intersection_print(&intersection);
	
	bool expected =
		intersection.shape == SPHERE &&
		intersection.count == 2 &&
		intersection.times[0] == -6.0f &&
		intersection.times[1] == -4.0f;
	
	RESULT("A sphere is behind a ray", expected);
}

void test_intersection_hit_1(void) {
	struct Intersection i1 = { .count = 2, .times = { 1.0f, 2.0f } };
	struct Hit hit = get_hit_from_intersections(&i1, 1);
	// hit_print(&hit);
	
	bool expected = hit.intersection == &i1 && hit.index == 0;
	RESULT("The hit, when all intersections have positive t", expected);
}

void test_intersection_hit_2(void) {
	struct Intersection i1 = { .count = 2, .times = { -1.0f, 1.0f } };
	struct Hit hit = get_hit_from_intersections(&i1, 1);
	// hit_print(&hit);
	
	bool expected = hit.intersection == &i1 && hit.index == 1;
	RESULT("The hit, when some intersections have negative t", expected);
}

void test_intersection_hit_3(void) {
	struct Intersection i1 = { .count = 2, .times = { -2.0f, -1.0f } };
	struct Hit hit = get_hit_from_intersections(&i1, 1);
	// hit_print(&hit);
	
	bool expected = !hit_is_valid(&hit);
	RESULT("The hit, when all intersections have negative t", expected);
}

void test_intersection_hit_4(void) {
	struct Intersection intersections[] = {
		{ .shape = SPHERE, .count = 2, .times = { 5.0f, 7.0f } },
		{ .shape = SPHERE, .count = 2, .times = { -3.0f, 2.0f } }
	};
	struct Hit hit = get_hit_from_intersections(intersections, 2);
	// hit_print(&hit);
	
	bool expected = hit.intersection == &intersections[1] && hit.index == 1;
	RESULT("The hit is always the lowest nonnegative intersection", expected);
}

void test_translating_ray(void) {
	struct Ray ray = new_ray(new_point(1.0f, 2.0f, 3.0f), new_vector(0.0f, 1.0f, 0.0f));
	union Matrix4x4 m = m4x4_translation(3.0f, 4.0f, 5.0f);
	struct Ray translated = ray_transform(&ray, &m);
	
	bool expected =
		tuple_eq(translated.origin, new_point(4.0f, 6.0f, 8.0f)) &&
		tuple_eq(translated.dir, new_vector(0.0f, 1.0f, 0.0f));
	
	RESULT("Translating a ray", expected);
}

void test_scaling_ray(void) {
	struct Ray ray = new_ray(new_point(1.0f, 2.0f, 3.0f), new_vector(0.0f, 1.0f, 0.0f));
	union Matrix4x4 m = m4x4_scaling(2.0f, 3.0f, 4.0f);
	struct Ray translated = ray_transform(&ray, &m);
	
	ray_print(&ray);
	ray_print(&translated);
	
	bool expected =
		tuple_eq(translated.origin, new_point(2.0f, 6.0f, 12.0f)) &&
		tuple_eq(translated.dir, new_vector(0.0f, 3.0f, 0.0f));
	
	RESULT("Scaling a ray", expected);
}

