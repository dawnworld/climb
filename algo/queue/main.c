#include <stdio.h>
#include "queue/queue.h"

static void each_data(void *data)
{
    int *p_data;

    p_data = (int *)data;

    printf("p_data:%p, *p_data:%d\n", p_data, *p_data);
    
    return;
}

void test_foreach_queue() {
    Queue *q = create_queue();
    printf("q:%p, len:%d\n", q, queue_len(q));

    int data = 5;
    enqueue(q, (void *)&data);
    printf("q:%p, len:%d\n", q, queue_len(q));

    foreach_queue(q, each_data);

    free_queue(q);
}

int main()
{
    test_foreach_queue();
    return 0;
}
