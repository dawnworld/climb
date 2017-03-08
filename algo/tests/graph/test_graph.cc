/*
 * test_graph.cc
 * Copyright (C) 2017 dawnworld <thundon@qq.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "gtest/gtest.h"
#include "graph/graph.h"
#include "graph/graph_search.h"
#include "graph/shortest_path.h"

#define TEST_SIZE (37)

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

TEST(GraphSearch, DirectDfs) {
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
    EXPECT_EQ(2, info->reached);

    search_info_reset(info);
    dfs(info, 0);
    EXPECT_EQ(5, info->reached);

    search_info_destroy(info);
    graph_destroy(g);
}

TEST(GraphSearch, DirectBfs) {
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

    bfs(info, 2);
    EXPECT_EQ(2, info->reached);

    search_info_reset(info);
    bfs(info, 0);
    EXPECT_EQ(5, info->reached);

    search_info_destroy(info);
    graph_destroy(g);
}

TEST(ShortestPath, BellmanFord) {
    int i;
    int dist[TEST_SIZE];
    int parent[TEST_SIZE];
    int ret;

    Graph g = graph_create(TEST_SIZE);
    ASSERT_TRUE(NULL != g);
    EXPECT_EQ(TEST_SIZE, graph_vertex_count(g));

    for(i = 0; i < TEST_SIZE - 2; i++) {
        graph_add_weighted_edge(g, i, i+1, -(2*i+1));
    }
    /* search from 0 */
    ret = bellman_ford(g, 0, dist, parent);
    EXPECT_EQ(0, ret);

    /* check distances */
    for(i = 0; i < TEST_SIZE - 2; i++) {
        EXPECT_EQ(dist[i], -i*i);
        ASSERT_TRUE(i == 0 || parent[i] == i-1);
    }

    graph_destroy(g);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
