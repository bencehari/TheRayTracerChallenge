#include "primitives.h"

static size_t objectId;

struct Sphere new_sphere() {
	return (struct Sphere) { objectId++, new_point(0.0f, 0.0f, 0.0f), 1.0f };
}
