#ifndef __KNAPSACK_H__
#define __KNAPSACK_H__

#include "utils/util.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct knapsack_ctx KsCtx;

KsCtx* ks_init(uint32 cap, uint32 num);
int ks_add_gem(uint16 volume, uint16 value, KsCtx* ctx);
uint32 ks_calc_max(KsCtx *ctx);
void ks_show_gems(char* buf, uint32 buf_len, KsCtx *ctx);
void ks_close(KsCtx *ctx);

#ifdef __cplusplus
}
#endif

#endif
