#include "gtest/gtest.h"
#include "dp/knapsack.h"

TEST(Knapsack, Init) {
    KsCtx *ks = ks_init(3, 1);
    ASSERT_TRUE(NULL != ks);

    ks_close(ks);
}

TEST(Knapsack, OneGem) {
    KsCtx *ks = ks_init(3, 1);
    ASSERT_TRUE(NULL != ks);

    EXPECT_EQ(1, ks_add_gem(1, 10, ks));
    EXPECT_EQ(10, ks_calc_max(ks));

    ks_close(ks);
}

TEST(Knapsack, ThreeGems) {
    KsCtx *ks = ks_init(3, 3);
    ASSERT_TRUE(NULL != ks);

    EXPECT_EQ(1, ks_add_gem(1, 10, ks));
    EXPECT_EQ(2, ks_add_gem(2, 1, ks));
    EXPECT_EQ(3, ks_add_gem(2, 5, ks));
    EXPECT_EQ(15, ks_calc_max(ks));

    ks_close(ks);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
