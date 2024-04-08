#ifndef TRTC_LOG_H
#define TRTC_LOG_H

#include <stdio.h>

#include "consc.h"

#define LOG(_m) printf("[%s:%d] %s\n", __FILE__, __LINE__, (_m))
#define LOG_W(_m) printf(AC_YELLOW "[%s:%d]" AC_RESET " %s\n", __FILE__, __LINE__, (_m))
#define LOG_E(_m) printf(AC_RED "[%s:%d]" AC_RESET " %s\n", __FILE__, __LINE__, (_m))

#endif // TRTC_LOG_H
