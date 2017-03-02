#include "queue/queue.h"
#include "gtest/gtest.h"

TEST(QueueBase, QueueAlloc) { 
    Queue *q = create_queue();
    ASSERT_TRUE(NULL != q);
    EXPECT_EQ (0, queue_len(q));

    free_queue(q);
}
 
TEST(QueueBase, Enqueue) {
   Queue *q = create_queue();
   ASSERT_TRUE(NULL != q);
   EXPECT_EQ (0, queue_len(q));

   int data = 5;
   EXPECT_EQ(1, enqueue(q, (void *)&data));
   EXPECT_EQ(1, queue_len(q));

   free_queue(q);
}

TEST(QueueBase, Dequeue) {
   Queue *q = create_queue();
   ASSERT_TRUE(NULL != q);
   EXPECT_EQ (0, queue_len(q));

   int data = 5;
   EXPECT_EQ(1, enqueue(q, (void *)&data));
   EXPECT_EQ(1, queue_len(q));

   void* p_data;
   p_data = dequeue(q);
   ASSERT_TRUE(p_data != NULL);
   EXPECT_EQ(0, queue_len(q));
   EXPECT_EQ(5, *(int *)p_data);

   free_queue(q);
}

static void each_data(void *data)
{
   int *p_data;

   ASSERT_TRUE(NULL != data);

   p_data = (int *)data;
   EXPECT_EQ(5, *p_data);
    
   return;
}

TEST(QueueBase, ForeachQueue) {
   Queue *q = create_queue();
   ASSERT_TRUE(NULL != q);
   EXPECT_EQ (0, queue_len(q));

   int data = 5;
   EXPECT_EQ(1, enqueue(q, (void *)&data));
   EXPECT_EQ(1, queue_len(q));

   foreach_queue(q, each_data);

   free_queue(q);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
