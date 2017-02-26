#include <string.h>
#include "queue/queue.h"

typedef struct node {
    void *data;
    struct node *next;
} Node;

typedef struct queue {
    Node *head;
    Node *tail;
    uint32 len;    
} Queue;


Queue* create_queue()
{
    Queue *queue = NULL;

    if (NULL == (queue = MALLOC(sizeof(Queue))))
        return NULL;

    memset(queue, 0, sizeof(Queue));

    return queue;
}

void free_queue(Queue *q)
{
    Node *node;
    
    if (NULL == q)
        return;

    for (node = q->head; node != NULL; node = node->next)
    {
        FREE(node);
        q->len--;
    }

    FREE(q);
}

uint32 enqueue(Queue *q, void *data)
{
    if (NULL == q || NULL == data)
        return 0;

    Node *node = NULL;

    if (NULL == (node = MALLOC(sizeof(Node))))
        return -1;

    memset(node, 0, sizeof(Node));
    node->data = data; 

    if (NULL != q->tail)
        q->tail->next = node;

    q->tail = node;

    if (NULL == q->head)
        q->head = node;

	return ++q->len;
}

void* dequeue(Queue *q)
{
    if (NULL == q || NULL == q->head)
        return NULL;

    Node *node = NULL;
    node = q->head;
    q->head = node->next;
    q->len--;

    if (NULL == q->head)
        q->tail = NULL;

	return node->data;
}

uint32 queue_len(Queue *q)
{
    if (NULL == q)
        return 0;

    return q->len;
}

void foreach_queue(Queue *q, each_cb cb)
{
    if (NULL == q || NULL == cb)
        return;

    Node *node;
    
    for (node = q->head; node != NULL; node = node->next)
        cb(node->data);
}
