/*
 * graph.h
 * Copyright (C) 2017 dawnworld <thundon@qq.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "utils/util.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct graph_t* Graph;

/* create a new graph with n vertices labeled 0..n-1 and no edges */
Graph graph_create(uint32 n);

/* free all space used by graph */
void graph_destroy(Graph);

/* add an edge to an existing graph */
/* doing this more than once may have unpredictable results */
void graph_add_edge(Graph, uint32 source, uint32 sink, bool_t direct);

/* return the number of vertices/edges in the graph */
uint32 graph_vertex_count(Graph);
uint32 graph_edge_count(Graph);

/* return the out-degree of a vertex */
uint32 graph_out_degree(Graph, uint32 source);

/* return 1 if edge (source, sink) exists), 0 otherwise */
uint32 graph_has_edge(Graph, uint32 source, uint32 sink);

/* invoke f on all edges (u,v) with source u */
/* supplying data as final parameter to f */
/* no particular order is guaranteed */
void graph_foreach(Graph g, uint32 source,
        void (*f)(Graph g, uint32 source, uint32 sink, void *data),
        void *data);

void graph_set_vertex_data(Graph g, uint32 v, void *data);
void* graph_get_vertex_data(Graph g , uint32 v);

/* dump all adjacency in current vertex */
void graph_dump_vertex(Graph g, uint32 v, char* buf, uint32 len);

#ifdef __cplusplus
}
#endif

#endif /* !__GRAPH_H__ */
