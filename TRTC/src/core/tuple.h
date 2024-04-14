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

static inline struct Tuple tuple_add(struct Tuple _a, struct Tuple _b) {
	return (struct Tuple) { _a.x + _b.x, _a.y + _b.y, _a.z + _b.z, _a.w + _b.w };
}

static inline void tuple_add_self(struct Tuple* _a, struct Tuple _b) {
	*_a = (struct Tuple) { _a->x + _b.x, _a->y + _b.y, _a->z + _b.z, _a->w + _b.w };
}

static inline struct Tuple tuple_sub(struct Tuple _a, struct Tuple _b) {
	return (struct Tuple) { _a.x - _b.x, _a.y - _b.y, _a.z - _b.z, _a.w - _b.w };
}

static inline void tuple_sub_self(struct Tuple* _a, struct Tuple _b) {
	*_a = (struct Tuple) { _a->x - _b.x, _a->y - _b.y, _a->z - _b.z, _a->w - _b.w };
}

static inline struct Tuple tuple_mul(struct Tuple _a, struct Tuple _b) {
	return (struct Tuple) { _a.x * _b.x, _a.y * _b.y, _a.z * _b.z, _a.w * _b.w };
}

static inline void tuple_mul_self(struct Tuple* _a, struct Tuple _b) {
	*_a = (struct Tuple) { _a->x * _b.x, _a->y * _b.y, _a->z * _b.z, _a->w * _b.w };
}

static inline struct Tuple tuple_mul_f(struct Tuple _a, float _b) {
	return (struct Tuple) { _a.x * _b, _a.y * _b, _a.z * _b, _a.w };
}

static inline void tuple_mul_f_self(struct Tuple* _a, float _b) {
	*_a = (struct Tuple) { _a->x * _b, _a->y * _b, _a->z * _b, _a->w };
}

static inline struct Tuple tuple_div(struct Tuple _a, struct Tuple _b) {
	return (struct Tuple) { _a.x / _b.x, _a.y / _b.y, _a.z / _b.z, _a.w / _b.w };
}

static inline void tuple_div_self(struct Tuple* _a, struct Tuple _b) {
	*_a = (struct Tuple) { _a->x / _b.x, _a->y / _b.y, _a->z / _b.z, _a->w / _b.w };
}

static inline struct Tuple tuple_div_f(struct Tuple _a, float _b) {
	return (struct Tuple) { _a.x / _b, _a.y / _b, _a.z / _b, _a.w };
}

static inline void tuple_div_f_self(struct Tuple* _a, float _b) {
	*_a = (struct Tuple) { _a->x / _b, _a->y / _b, _a->z / _b, _a->w };
}

// negate
static inline struct Tuple tuple_neg(struct Tuple _t) {
	return (struct Tuple) { -_t.x, -_t.y, -_t.z, -_t.w };
}

static inline void tuple_neg_self(struct Tuple* _t) {
	*_t = (struct Tuple) { -_t->x, -_t->y, -_t->z, -_t->w };
}

// magnitude
static inline float tuple_mag(struct Tuple _t) {
	return sqrtf(_t.x * _t.x + _t.y * _t.y + _t.z * _t.z);
}

// normal
static inline struct Tuple tuple_norm(struct Tuple _t) {
	float m_ag = tuple_mag(_t);
	return tuple_div_f(_t, m_ag);
}

static inline void tuple_norm_self(struct Tuple* _t) {
	float m_ag = tuple_mag(*_t);
	*_t = tuple_div_f(*_t, m_ag);
}

static inline float tuple_dot(struct Tuple _a, struct Tuple _b) {
	return
		_a.x * _b.x +
		_a.y * _b.y +
		_a.z * _b.z +
		_a.w * _a.w;
}

static inline struct Tuple tuple_cross(struct Tuple _a, struct Tuple _b) {
	return (struct Tuple) {
		_a.y * _b.z - _a.z * _b.y,
		_a.z * _b.x - _a.x * _b.z,
		_a.x * _b.y - _a.y * _b.x
	};	
}

static inline void tuple_print(struct Tuple* _t) {
	printf(
		"{ x: %.3f, y: %.3f, z: %.3f, w: %.3f }\n",
		_t->x, _t->y, _t->z, _t->w);
}

#endif // TRTC_TUPLE_H
