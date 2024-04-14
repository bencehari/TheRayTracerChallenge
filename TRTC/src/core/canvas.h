#ifndef TRTC_CANVAS_H
#define TRTC_CANVAS_H

#include <stdint.h>
#include <stdbool.h>

#include "color.h"

extern bool canvas_initialize(int _width, int _height, struct Color _clearColor);

extern void canvas_cleanup(void);

extern void canvas_set_pixel(int _x, int _y, struct Color _c);

// extern void canvas_get_as_int_array(uint8_t _colors[]);

extern void canvas_save_to_ppm(const char* _name);

#endif // TRTC_CANVAS_H
