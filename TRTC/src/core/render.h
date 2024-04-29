#ifndef TRTC_CORE_H
#define TRTC_CORE_H

#include <stdint.h>
#include <stdbool.h>

extern int render_init(const int _width, const int _height);

extern void render_set_screen(uint32_t _pixels[]);
extern void render_update_screen(uint32_t* (*_getPixels)(void));

extern void render_cleanup(void);

#endif // TRTC_CORE_H
