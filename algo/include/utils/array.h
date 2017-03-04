#ifndef __UTILS_ARRAY_H__
#define __UTILS_ARRAY_H__

#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif

void** alloc_2d_array(uint32 r, uint32 c, uint32 size);
void free_2d_array(void** array);

#ifdef __cplusplus
}
#endif

#endif