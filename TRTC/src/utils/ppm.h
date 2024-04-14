#ifndef TRTC_PPM_H
#define TRTC_PPM_H

#include <stdint.h>

enum PPM_ErrCode {
	PPM_NONE,
	PPM_FILE,
	PPM_HEADER,
	PPM_WRITE
};

/**
 * @brief Saves data to 'plain' Portable Pixmap.
 * @param _name Output filename without extension.
 * @param _width Width
 * @param _height Height
 * @param _colors Colors represented between 0-255.
 */
enum PPM_ErrCode ppm_save(const char* _name, const int _width, const int _height, const uint8_t _colors[]);

#endif // TRTC_PPM_H
