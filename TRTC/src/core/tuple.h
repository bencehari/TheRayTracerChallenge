#ifndef TRTC_TUPLE_H
#define TRTC_TUPLE_H

#include <stdio.h>
#include <math.h>

struct Tuple {
	float x, y, z, w;
};

static inline struct Tuple new_vector(float _x, float  _y, float _z) {
	return (struct Tuple) { _x, _y, _z, .0f };
}

static inline struct Tuple new_point(float _x, float _y, float _z) {
	return (struct Tuple) { _x, _y, _z, 1.0f };
}

static inline struct Tuple Tuple_add(struct Tuple _a, struct Tuple _b) {
	return (struct Tuple) { _a.x + _b.x, _a.y + _b.y, _a.z + _b.z, _a.w + _b.w };
}

static inline struct Tuple Tuple_sub(struct Tuple _a, struct Tuple _b) {
	return (struct Tuple) { _a.x - _b.x, _a.y - _b.y, _a.z - _b.z, _a.w - _b.w };
}

static inline struct Tuple Tuple_mul(struct Tuple _a, struct Tuple _b) {
	return (struct Tuple) { _a.x * _b.x, _a.y * _b.y, _a.z * _b.z, _a.w * _b.w };
}

static inline struct Tuple Tuple_mul_f(struct Tuple _a, float _b) {
	return (struct Tuple) { _a.x * _b, _a.y * _b, _a.z * _b, _a.w };
}

static inline struct Tuple Tuple_div(struct Tuple _a, struct Tuple _b) {
	return (struct Tuple) { _a.x / _b.x, _a.y / _b.y, _a.z / _b.z, _a.w / _b.w };
}

static inline struct Tuple Tuple_div_f(struct Tuple _a, float _b) {
	return (struct Tuple) { _a.x / _b, _a.y / _b, _a.z / _b, _a.w };
}

// negate
static inline struct Tuple Tuple_neg(struct Tuple _a) {
	return (struct Tuple) { -_a.x, -_a.y, -_a.z, -_a.w };
}

// magnitude
static inline float Tuple_mag(struct Tuple _a) {
	return sqrtf(_a.x * _a.x + _a.y * _a.y + _a.z * _a.z);
}

// normal
static inline struct Tuple Tuple_norm(struct Tuple _t) {
	float m_ag = Tuple_mag(_t);
	return Tuple_div_f(_t, m_ag);
}

static inline float Tuple_dot(struct Tuple _a, struct Tuple _b) {
	return
		_a.x * _b.x +
		_a.y * _b.y +
		_a.z * _b.z +
		_a.w * _a.w;
}

static inline struct Tuple Tuple_cross(struct Tuple _a, struct Tuple _b) {
	return (struct Tuple) {
		_a.y * _b.z - _a.z * _b.y,
		_a.z * _b.x - _a.x * _b.z,
		_a.x * _b.y - _a.y * _b.x
	};	
}

static inline void print_Tuple(struct Tuple* _t) {
	printf(
		"{ x: %.3f, y: %.3f, z: %.3f, w: %.3f }\n",
		_t->x, _t->y, _t->z, _t->w);
}

#endif // TRTC_TUPLE_H
