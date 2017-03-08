/*
 * shortest_path.h
 * Copyright (C) 2017 dawnworld <thundon@qq.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef __SHORTEST_PATH_H__
#define __SHORTEST_PATH_H__

#include "graph/graph.h"

#ifdef __cplusplus
extern "C" {
#endif

/* various algorithms for shortest paths */

#define SHORTEST_PATH_NULL_PARENT (-1)

/* Computes distance of each node from starting node */
/* and stores results in dist (length n, allocated by the caller) */
/* unreachable nodes get distance MAXINT */
/* If parent argument is non-null, also stores parent pointers in parent */
/* Allows negative-weight edges and runs in O(nm) time. */
/* returns 1 if there is a negative cycle, 0 otherwise */
int bellman_ford(Graph g, int source, int *dist, int *parent);

/* computes all-pairs shortest paths using Floyd-Warshall given */
/* an adjacency matrix */
/* answer is returned in the provided matrix! */
/* assumes matrix is n pointers to rows of n ints each */
void floyd_warshall(int n, int **matrix);

#define DIJKSTRA_NULL_PARENT (-1)

/* Computes distance of each node from starting node */
/* and stores results in dist (length n, allocated by the caller) */
/* unreachable nodes get distance MAXINT */
/* If parent argument is non-null, also stores parent pointers in parent */
/* Assumes no negative-weight edges */
/* Runs in O(n + m log m) time. */
/* Note: uses pq structure from pq.c */
void dijkstra(Graph g, int source, int *dist, int *parent);

#ifdef __cplusplus
}
#endif

#endif /* !__SHORTEST_PATH_H__ */
