#ifndef TRTC_TUPLE_H
#define TRTC_TUPLE_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

union Tuple {
	struct {
		float x, y, z, w;
	};
	float e[4];
};

#define TUPLE(_x, _y, _z, _w) (union Tuple) {{ (_x), (_y), (_z), (_w) }}

static inline bool tuple_eq(union Tuple _t0, union Tuple _t1) {
	return _t0.e[0] == _t1.e[0] && _t0.e[1] == _t1.e[1] && _t0.e[2] == _t1.e[2] && _t0.e[3] == _t1.e[3];
}

static inline union Tuple new_vector(float _x, float  _y, float _z) {
	return TUPLE(_x, _y, _z, 0.0f);
}

static inline union Tuple new_point(float _x, float _y, float _z) {
	return TUPLE(_x, _y, _z, 1.0f);
}

static inline union Tuple tuple_add(union Tuple _a, union Tuple _b) {
	return TUPLE(_a.x + _b.x, _a.y + _b.y, _a.z + _b.z, _a.w + _b.w);
}

static inline void tuple_add_self(union Tuple* _a, union Tuple _b) {
	*_a = TUPLE(_a->x + _b.x, _a->y + _b.y, _a->z + _b.z, _a->w + _b.w);
}

static inline union Tuple tuple_sub(union Tuple _a, union Tuple _b) {
	return TUPLE(_a.x - _b.x, _a.y - _b.y, _a.z - _b.z, _a.w - _b.w);
}

static inline void tuple_sub_self(union Tuple* _a, union Tuple _b) {
	*_a = TUPLE(_a->x - _b.x, _a->y - _b.y, _a->z - _b.z, _a->w - _b.w);
}

static inline union Tuple tuple_mul(union Tuple _a, union Tuple _b) {
	return TUPLE(_a.x * _b.x, _a.y * _b.y, _a.z * _b.z, _a.w * _b.w);
}

static inline void tuple_mul_self(union Tuple* _a, union Tuple _b) {
	*_a = TUPLE(_a->x * _b.x, _a->y * _b.y, _a->z * _b.z, _a->w * _b.w);
}

static inline union Tuple tuple_mul_f(union Tuple _a, float _b) {
	return TUPLE(_a.x * _b, _a.y * _b, _a.z * _b, _a.w);
}

static inline void tuple_mul_f_self(union Tuple* _a, float _b) {
	*_a = TUPLE(_a->x * _b, _a->y * _b, _a->z * _b, _a->w);
}

static inline union Tuple tuple_div(union Tuple _a, union Tuple _b) {
	return TUPLE(_a.x / _b.x, _a.y / _b.y, _a.z / _b.z, _a.w / _b.w);
}

static inline void tuple_div_self(union Tuple* _a, union Tuple _b) {
	*_a = TUPLE(_a->x / _b.x, _a->y / _b.y, _a->z / _b.z, _a->w / _b.w);
}

static inline union Tuple tuple_div_f(union Tuple _a, float _b) {
	return TUPLE(_a.x / _b, _a.y / _b, _a.z / _b, _a.w);
}

static inline void tuple_div_f_self(union Tuple* _a, float _b) {
	*_a = TUPLE(_a->x / _b, _a->y / _b, _a->z / _b, _a->w);
}

// negate
static inline union Tuple tuple_neg(union Tuple _t) {
	return TUPLE(-_t.x, -_t.y, -_t.z, -_t.w);
}

static inline void tuple_neg_self(union Tuple* _t) {
	*_t = TUPLE(-_t->x, -_t->y, -_t->z, -_t->w);
}

// magnitude
static inline float tuple_mag(union Tuple _t) {
	return sqrtf(_t.x * _t.x + _t.y * _t.y + _t.z * _t.z);
}

// normal
static inline union Tuple tuple_norm(union Tuple _t) {
	float m_ag = tuple_mag(_t);
	return tuple_div_f(_t, m_ag);
}

static inline void tuple_norm_self(union Tuple* _t) {
	float m_ag = tuple_mag(*_t);
	*_t = tuple_div_f(*_t, m_ag);
}

static inline float tuple_dot(union Tuple _a, union Tuple _b) {
	return
		_a.x * _b.x +
		_a.y * _b.y +
		_a.z * _b.z +
		_a.w * _a.w;
}

static inline union Tuple tuple_cross(union Tuple _a, union Tuple _b) {
	return TUPLE(
		_a.y * _b.z - _a.z * _b.y,
		_a.z * _b.x - _a.x * _b.z,
		_a.x * _b.y - _a.y * _b.x,
		0.0f);
}

static inline void tuple_print(union Tuple* _t) {
	printf(
		"{ x: %.3f, y: %.3f, z: %.3f, w: %.3f }\n",
		_t->x, _t->y, _t->z, _t->w);
}

static inline bool tuple_is_point(union Tuple* _t) {
	return _t->w != 0.0f;
}

static inline bool tuple_is_vector(union Tuple* _t) {
	return _t->w == 0.0f;
}

#endif // TRTC_TUPLE_H
