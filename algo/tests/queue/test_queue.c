#include "check.h"
#include "ut.h"
#include "queue/queue.h"

#define SUITE_NAME "test"
#define TCASE_NAME "cases"

START_TEST(test_create_queue) {
    Queue *q = create_queue();
    ck_assert(NULL != q);
    ck_assert(queue_len(q) == 0);

    free_queue(q);
}
END_TEST

START_TEST(test_enqueue) {
    Queue *q = create_queue();
    ck_assert(NULL != q);
    ck_assert(queue_len(q) == 0);

    int data = 5;
    ck_assert(enqueue(q, (void *)&data) == 1);
    ck_assert(queue_len(q) == 1);

    free_queue(q);
}
END_TEST

START_TEST(test_dequeue) {
    Queue *q = create_queue();
    ck_assert(NULL != q);
    ck_assert(queue_len(q) == 0);

    int data = 5;
    ck_assert(enqueue(q, (void *)&data) == 1);
    ck_assert(queue_len(q) == 1);

    void* p_data;
    p_data = dequeue(q);
    ck_assert(p_data != NULL);
    ck_assert(queue_len(q) == 0);
    ck_assert(*(int *)p_data == 5);

    free_queue(q);
}
END_TEST

static void each_data(void *data)
{
    int *p_data;

    ck_assert(NULL != data);

    p_data = (int *)data;
    ck_assert(*p_data == 5);
    
    return;
}

START_TEST(test_foreach_queue) {
    Queue *q = create_queue();
    ck_assert(NULL != q);
    ck_assert(queue_len(q) == 0);

    int data = 5;
    ck_assert(enqueue(q, (void *)&data) == 1);
    ck_assert(queue_len(q) == 1);

    foreach_queue(q, each_data);

    free_queue(q);
}
END_TEST

Suite * make_test_suite(void) {
    /* 建立Suite */
    Suite *s = suite_create(SUITE_NAME);

    /* 建立测试用例集 */
    TCase *tcs = tcase_create(TCASE_NAME);

    /* 将测试用例加到Suite中 */
    suite_add_tcase(s, tcs);

    /* 测试用例加到测试集中 */
    tcase_add_test(tcs, test_create_queue);
    tcase_add_test(tcs, test_enqueue);
    tcase_add_test(tcs, test_dequeue);
    tcase_add_test(tcs, test_foreach_queue);

    return s;
}
