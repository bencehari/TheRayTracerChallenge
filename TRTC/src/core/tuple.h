#ifndef TRTC_TUPLE_H
#define TRTC_TUPLE_H

#include <stdio.h>
#include <math.h>

struct tuple {
	float x, y, z, w;
};

static inline struct tuple new_vector(float _x, float  _y, float _z) {
	return { _x, _y, _z, .0f };
}

static inline struct tuple new_point(float _x, float _y, float _z) {
	return { _x, _y, _z, 1.0f };
}

static inline struct tuple tuple_add(struct tuple _a, struct tuple _b) {
	return { _a.x + _b.x, _a.y + _b.y, _a.z + _b.z, _a.w + _b.w };
}

static inline struct tuple tuple_sub(struct tuple _a, struct tuple _b) {
	return { _a.x - _b.x, _a.y - _b.y, _a.z - _b.z, _a.w - _b.w };
}

static inline struct tuple tuple_mul(struct tuple _a, struct tuple _b) {
	return { _a.x * _b.x, _a.y * _b.y, _a.z * _b.z, _a.w * _b.w };
}

static inline struct tuple tuple_mul_f(struct tuple _a, float _b) {
	return { _a.x * _b, _a.y * _b, _a.z * _b, _a.w };
}

static inline struct tuple tuple_div(struct tuple _a, struct tuple _b) {
	return { _a.x / _b.x, _a.y / _b.y, _a.z / _b.z, _a.w / _b.w };
}

static inline struct tuple tuple_div_f(struct tuple _a, float _b) {
	return { _a.x / _b, _a.y / _b, _a.z / _b, _a.w };
}

// negate
static inline struct tuple tuple_neg(struct tuple _a) {
	return { -_a.x, -_a.y, -_a.z, -_a.w };
}

// magnitude
static inline float tuple_mag(struct tuple _a) {
	return sqrtf(_a.x * _a.x + _a.y * _a.y + _a.z * _a.z);
}

// normal
static inline struct tuple tuple_norm(struct tuple _t) {
	float m_ag = tuple_m_ag(_t);
	return tuple_div_f(_t, m_ag);
}

static inline float tuple_dot(struct tuple _a, struct tuple _b) {
	return
		_a.x * _b.x +
		_a.y * _b.y +
		_a.z * _b.z +
		_a.w * _a.w;
}

static inline struct tuple tuple_cross(struct tuple _a, struct tuple _b) {
	return {
		_a.y * _b.z - _a.z * _b.y,
		_a.z * _b.x - _a.x * _b.z,
		_a.x * _b.y - _a.y * _b.x
	};	
}

static inline void print_tuple(struct tuple* _t) {
	printf(
		"{ x: %.3f, y: %.3f, z: %.3f, w: %.3f }\n",
		_t->x, _t->y, _t->z, _t->w);
}

#endif // TRTC_TUPLE_H
