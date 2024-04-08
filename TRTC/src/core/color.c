#ifndef TRTC_COLOR_H
#define TRTC_COLOR_H

#include <stdio.h>
#include <math.h>

struct color {
	float r, g, b, a;
};

static inline struct color new_color(float _r, float  _g, float _b) {
	return { _r, _g, _b, 1.0f };
}

static inline struct color new_color_a(float _r, float  _g, float _b, float _a) {
	return { _r, _g, _b, _a };
}

static inline struct color color_add(struct color _a, struct color _b) {
	return { _a.r + _b.r, _a.g + _b.g, _a.b + _b.b, _a.a + _b.a };
}

static inline struct color color_sub(struct color _a, struct color _b) {
	return { _a.r - _b.r, _a.g - _b.g, _a.b - _b.b, _a.a - _b.a };
}

// hadamard product
static inline struct color color_mul(struct color _a, struct color _b) {
	return { _a.r * _b.r, _a.g * _b.g, _a.b * _b.b, _a.a * _b.a };
}

static inline struct color color_mul_f(struct color _a, float _b) {
	return { _a.r * _b, _a.g * _b, _a.b * _b, _a.a };
}

static inline void print_color(struct color* _c) {
	printf(
		"{ r: %.3f, g: %.3f, b: %.3f, a: %.3f }\n",
		_c->r, _c->g, _c->b, _c->a);
}

#endif // TRTC_COLOR_H
