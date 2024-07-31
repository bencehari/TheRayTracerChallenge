#ifndef TRTC_TESTS_H
#define TRTC_TESTS_H

#include "../utils/consc.h"

#define EVALUATE(_expr) ((_expr) ? (AC_GREEN "PASS" AC_RESET) : (AC_RED "FAIL" AC_RESET))
#define RESULT(_text, _eval_expr) (printf(_text": %s\n", EVALUATE((_eval_expr))))

extern int test_draw_trajectory(void);
extern void test_matrices(void);
extern void test_transformations(void);
extern void test_ray_sphere_intersections(void);

#endif // TRTC_TESTS_H
