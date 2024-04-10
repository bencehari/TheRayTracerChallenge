#ifndef TRTC_CANVAS_H
#define TRTC_CANVAS_H

#include <stdbool.h>

#include "color.h"

extern bool canvas_initialize(int _width, int _height);

extern void canvas_cleanup(void);

extern void canvas_set_pixel(int _x, int _y, struct Color _c);

extern int canvas_get_pixel_count(void);

extern void canvas_get_as_int_array(int _colors[]);

#endif // TRTC_CANVAS_H
