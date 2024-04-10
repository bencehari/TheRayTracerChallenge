#ifndef TRTC_COLOR_H
#define TRTC_COLOR_H

#include <stdio.h>
#include <math.h>

struct Color {
	float r, g, b, a;
};

static inline struct Color new_color(float _r, float  _g, float _b) {
	return (struct Color) { _r, _g, _b, 1.0f };
}

#define COLOR_WHITE new_color(1.0f, 1.0f, 1.0f)
#define COLOR_BLACK new_color(.0f, .0f, .0f)

static inline struct Color new_color_a(float _r, float  _g, float _b, float _a) {
	return (struct Color) { _r, _g, _b, _a };
}

static inline struct Color color_add(struct Color _a, struct Color _b) {
	return (struct Color) { _a.r + _b.r, _a.g + _b.g, _a.b + _b.b, _a.a + _b.a };
}

static inline struct Color color_sub(struct Color _a, struct Color _b) {
	return (struct Color) { _a.r - _b.r, _a.g - _b.g, _a.b - _b.b, _a.a - _b.a };
}

// hadamard product
static inline struct Color color_mul(struct Color _a, struct Color _b) {
	return (struct Color) { _a.r * _b.r, _a.g * _b.g, _a.b * _b.b, _a.a * _b.a };
}

static inline struct Color color_mul_f(struct Color _a, float _b) {
	return (struct Color) { _a.r * _b, _a.g * _b, _a.b * _b, _a.a };
}

static inline void print_color(struct Color* _c) {
	printf(
		"{ r: %.3f, g: %.3f, b: %.3f, a: %.3f }\n",
		_c->r, _c->g, _c->b, _c->a);
}

#endif // TRTC_COLOR_H
