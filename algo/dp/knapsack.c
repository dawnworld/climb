#include "utils/util.h"
#include "dp/dp.h"
#include <string.h>
#include <stdio.h>

#include "gdsl/gdsl_2darray.h"

#define _2D_ARRAY_ALLOC(N, R, C) gdsl_2darray_alloc(N, R, C, NULL, NULL)
#define _2D_ARRAY_SET(R, C, D) gdsl_2darray_set_content(w, R, C, (void *)D)
#define _2D_ARRAY_GET(R, C) (uint32)gdsl_2darray_get_content(w, R, C)
#define _2D_ARRAY_FREE(A) gdsl_2darray_free((gdsl_2darray_t)A)

typedef gdsl_2darray_t _2D_ARRAY;

typedef struct gem {
    uint16  volume;
    uint16  value;
    uint8   put;
} Gem;

typedef struct knapsack_ctx {
    uint32  capacity;
    uint16  gem_num;    
    uint16  gem_added;
    Gem*    gem_array;
    void*   results;
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

    uint16 i = 0, j = 0;
    Gem* gem = NULL;
    uint32 result = 0;
    _2D_ARRAY w;

    w = _2D_ARRAY_ALLOC("gems", ctx->gem_added + 1, ctx->capacity + 1);

    for(i = 0; i <= ctx->gem_added; i++)
        _2D_ARRAY_SET(i, 0, 0);
    
    for(j = 0; j <= ctx->capacity; j++)
        _2D_ARRAY_SET(0, j, 0);

    for(i = 1; i <= ctx->gem_added; i++)
    {
        gem = ctx->gem_array + i;

        for(j = 1; j <= ctx->capacity; j++)
        {
            if(gem->volume > j)
            {
                _2D_ARRAY_SET(i, j, _2D_ARRAY_GET(i - 1, j));
                // w[i][j] = w[i - 1][j];
            }
            else
            {
                _2D_ARRAY_SET(i, j,
                        MAX(_2D_ARRAY_GET(i - 1, j),
                            _2D_ARRAY_GET(i - 1, j - gem->volume) + gem->value)
                        );
            }
        }
    }

    result = _2D_ARRAY_GET(ctx->gem_added, ctx->capacity);

    ctx->results = (void *)w;

    return result;
}

void ks_show_gems(char* buf, uint32 buf_len, KsCtx *ctx)
{
    int i = 0, j = 0;
    _2D_ARRAY w  = NULL;
    Gem *gem    = NULL;
    uint32  len = buf_len;

    if(NULL == buf || 0 == buf_len || NULL == ctx)
        return;

    if(NULL == ctx->results || NULL == ctx->gem_array)
        return;

    w = ctx->results;
    for(i = ctx->gem_added, j = ctx->capacity; i > 0; i--)
    {
        if(_2D_ARRAY_GET(i, j) > _2D_ARRAY_GET(i - 1, j))
        {
            gem = ctx->gem_array + i;
            gem->put = TRUE;
            j -= gem->volume;
        }
    }

    for(i = 1; i <= ctx->gem_added; i++)
    {
        gem = ctx->gem_array + i;
        if(TRUE == gem->put)
        {
            len = strnlen(buf, buf_len);
            buf += snprintf(buf, buf_len - len, "(%u,%u) ", gem->volume, gem->value);
        }
    }
}

void ks_close(KsCtx *ctx)
{
    if(NULL == ctx)
        return;

    if(NULL != ctx->gem_array)
        FREE(ctx->gem_array);

    if(NULL != ctx->results)
        _2D_ARRAY_FREE(ctx->results);

    FREE(ctx);
}
