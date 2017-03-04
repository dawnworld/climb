#ifndef __DP_H__
#define __DP_H__

#include "utils/util.h"

typedef struct knapsack_ctx KsCtx;

KsCtx* ks_init(uint32 cap, uint32 num);
int ks_add_gem(uint16 volume, uint16 value, KsCtx* ctx);
uint32 ks_calc_max(KsCtx *ctx);

#endif
