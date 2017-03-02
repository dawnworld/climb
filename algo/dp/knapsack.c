#include "common/common.h"
#include "dp/dp.h"
#include <string.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))

typedef struct gem {
    uint16  volume;
    uint16  value;
} Gem;

typedef struct knapsack_ctx {
    uint32  capacity;
    uint16  gem_num;    
    uint16  gem_added;
    Gem*    gem_array;
} KsCtx;

KsCtx* ks_init(uint32 cap, uint32 num)
{
    if(0 == cap || 0 == num)
        return NULL;

    KsCtx *ks_ctx = (KsCtx *)MALLOC(sizeof(KsCtx));
    if(NULL == ks_ctx)
        return NULL;

    memset(ks_ctx, 0, sizeof(KsCtx));

    ks_ctx->capacity = cap;
    ks_ctx->gem_num = num;
    ks_ctx->gem_array = MALLOC(sizeof(Gem) * (num + 1));

    return ks_ctx;
}

int ks_add_gem(uint16 volume, uint16 value, KsCtx* ctx)
{
    if(0 == volume || 0 == value || NULL == ctx)
        return -1;

    if(ctx->gem_added == ctx->gem_num)
        return 0;

    Gem *gem = ctx->gem_array + ++ctx->gem_added;
    gem->volume = volume;
    gem->value = value;

    return ctx->gem_added;
} 

uint32 ks_calc_max(KsCtx *ctx)
{
    if(NULL == ctx || 0 == ctx->gem_added || 0 == ctx->capacity)
        return 0;

    uint32** w = NULL;
    uint16 i = 0, j = 0;
    Gem* gem = NULL;
    uint32 result = 0;

    w = (uint32 **) MALLOC(sizeof(uint32) * (ctx->gem_added + 1));
    for(i = 0; i <= ctx->gem_added; i++)
        w[i] = (uint32 *) MALLOC(sizeof(uint32) * (ctx->capacity + 1));

    for(i = 0; i <= ctx->gem_added; i++)
        w[i][0] = 0;
    
    for(j = 0; j <= ctx->capacity; j++)
        w[0][j] = 0;

    for(i = 1; i <= ctx->gem_added; i++)
    {
        gem = ctx->gem_array + i;

        for(j = 1; j <= ctx->capacity; j++)
        {
            if(gem->volume > j)
            {
                w[i][j] = w[i - 1][j];
            }
            else
            {
                w[i][j] = MAX(w[i - 1][j], w[i - 1][j - gem->volume] + gem->value);
            }
        }
    }

    result = w[ctx->gem_added][ctx->capacity];
    FREE(w);

    return result;
}

void ks_close(KsCtx *ctx)
{
    if(NULL == ctx)
        return;

    if(NULL != ctx->gem_array)
        FREE(ctx->gem_array);

    FREE(ctx);
}
