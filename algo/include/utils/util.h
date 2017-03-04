#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------ Macro ---------------*/

#define MALLOC 		malloc
#define FREE   		free

#define TRUE        (1)
#define FALSE       (0)

#define MAX(A, B) 	((A) > (B) ? (A) : (B))
#define MIN(A, B) 	((A) < (B) ? (A) : (B))

typedef unsigned int    uint32;
typedef unsigned short  uint16;
typedef unsigned char   uint8;

#ifdef __cplusplus
}
#endif

#endif
