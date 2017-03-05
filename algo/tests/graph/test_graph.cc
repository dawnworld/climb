/*
 * test_graph.cc
 * Copyright (C) 2017 dawnworld <thundon@qq.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "gtest/gtest.h"
#include "graph/graph.h"
#include "graph/graph_search.h"

TEST(GraphBasic, Create) {
    Graph g = graph_create(10);
    ASSERT_TRUE(NULL != g);

    EXPECT_EQ(10, graph_vertex_count(g));

    graph_destroy(g);
}

TEST(GraphBasic, AddEdge) {
    Graph g = graph_create(10);
    ASSERT_TRUE(NULL != g);

    EXPECT_EQ(10, graph_vertex_count(g));

    graph_add_edge(g, 0, 1, TRUE);
    EXPECT_EQ(1, graph_edge_count(g));


    graph_add_edge(g, 0, 1, TRUE);
    graph_add_edge(g, 0, 1, TRUE);
    graph_add_edge(g, 0, 2, TRUE);
    graph_add_edge(g, 0, 2, TRUE);
    graph_add_edge(g, 0, 3, TRUE);
    graph_add_edge(g, 0, 1, TRUE);

    graph_add_edge(g, 1, 1, TRUE);
    graph_add_edge(g, 1, 0, TRUE);

    EXPECT_EQ(4, graph_edge_count(g));

    char buf[256] = {0};
    graph_dump_vertex(g, 0, buf, sizeof(buf));
    EXPECT_STREQ("(0->1) (0->2) (0->3) ", buf);

    graph_dump_vertex(g, 1, buf, sizeof(buf));
    EXPECT_STREQ("(1->0) ", buf);

    graph_destroy(g);
}

TEST(GraphSearch, dfs) {
    Graph g = graph_create(10);
    ASSERT_TRUE(NULL != g);
    EXPECT_EQ(10, graph_vertex_count(g));

    graph_add_edge(g, 0, 1, TRUE);
    graph_add_edge(g, 0, 2, TRUE);
    graph_add_edge(g, 0, 4, TRUE);
    graph_add_edge(g, 2, 3, TRUE);
    graph_add_edge(g, 4, 3, TRUE);
    EXPECT_EQ(5, graph_edge_count(g));

    search_info * info = search_info_create(g);
    ASSERT_TRUE(NULL != info);

    dfs(info, 2);
    EXPECT_EQ(1, info->reached);

    search_info_destroy(info);
    graph_destroy(g);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
