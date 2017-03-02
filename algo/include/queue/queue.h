#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "common/common.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct queue Queue;
    typedef void (*each_cb)(void *data);

    Queue* create_queue();
    void free_queue(Queue *q);

    uint32 enqueue(Queue *q, void *data);
    void* dequeue(Queue *q);
    uint32 queue_len(Queue *q);
    void foreach_queue(Queue *q, each_cb cb);

#ifdef __cplusplus
}
#endif

#endif
