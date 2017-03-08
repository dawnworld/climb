/*
 * graph.c
 * Copyright (C) 2017 dawnworld <thundon@qq.com>
 *
 * Distributed under terms of the MIT license.
 */


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "utils/util.h"
#include "graph/graph.h"

/* basic directed graph type */
/* the implementation uses adjacency lists
 * represented as variable-length arrays */

/* these arrays may or may not be sorted: if one gets long enough
 * and you call graph_has_edge on its source, it will be */

typedef struct vertex_t {
    uint32              id;
    bool_t              is_sorted;
    void*               data;
    uint32              adjs_len;
    uint32              adjs_num;
    struct adj {
        struct vertex_t*    v; /* vertex */
        int                 w; /* weight */
    } * adjs[1];
} Vertex;

struct graph_t {
    uint32      n;              /* number of vertices */
    uint32      m;              /* number of edges */
    struct vertex_t* vertices[1]; /* vertices */
};

/* create a new graph with n vertices labeled 0..n-1 and no edges */
Graph
graph_create(uint32 n)
{
    Graph g = NULL;

    uint32 i = 0;
    Vertex* v = NULL;

    g = MALLOC(sizeof(struct graph_t) + sizeof(struct vertex_t *) * (n-1));
    assert(g);

    g->n = n;
    g->m = 0;

    for(i = 0; i < n; i++) {
        v = MALLOC(sizeof(struct vertex_t));
        assert(v);

        v->id = i;
        v->is_sorted = TRUE;
        v->data = NULL;
        v->adjs_len = 1;
        v->adjs_num = 0;

        g->vertices[i] = v;
    }
    
    return g;
}

/* free all space used by graph */
void
graph_destroy(Graph g)
{
    uint32 i = 0, j = 0;
    struct vertex_t *v;


    for(i = 0; i < g->n; i++)
    {
        v = g->vertices[i];
        for(j = 0; j < v->adjs_num; j++)
            FREE(v->adjs[j]);
        
        FREE(v);
    }

    FREE(g);
}

/* add an edge to an existing graph */
static void
_graph_add_edge(Graph g, uint32 u, uint32 v)
{
    struct vertex_t *src    = NULL;
    struct vertex_t *sink   = NULL;
    uint32 i = 0;

    assert(u < g->n);
    assert(v < g->n);

    if(u == v) return;

    src = g->vertices[u];
    sink = g->vertices[v];
    /* do we need to grow the list? */
    if(src->adjs_num >= src->adjs_len)
    {
        src->adjs_len *= 2;
        src = REALLOC(src, 
                      sizeof(struct vertex_t)
                        + sizeof(struct adj) * (src->adjs_len  - 1));
        g->vertices[u] = src;
    }

    /* check if we have already build the edge */
    for(i = 0; i < src->adjs_num; i++)
    {
        if(src->adjs[i]->v == sink)
            return;
    }

    struct adj* e = (struct adj*)MALLOC(sizeof(struct adj));
    e->w = 0;
    e->v = sink;

    /* now add the new sink */
    src->adjs[src->adjs_num++] = e;
    src->is_sorted = FALSE;

    /* bump edge count */
    g->m++;
}

static void
_graph_set_edge_weight(Graph g, uint32 u, uint32 v, int w)
{
    struct vertex_t *src = NULL, *sink = NULL;
    uint32 i = 0;

    src = g->vertices[u];
    for(i = 0; i < src->adjs_num; i++)
    {
        sink = src->adjs[i]->v;
        if(sink->id != v)
            continue;
        src->adjs[i]->w = w;
    }

}

void
graph_add_edge(Graph g, uint32 u, uint32 v, bool_t directed)
{
    _graph_add_edge(g, u, v);
    if(FALSE == directed)
        _graph_add_edge(g, v, u);
}

/* add an edge to an existing graph */
void
graph_add_weighted_edge(Graph g, int u, int v, int wt)
{
    assert(u >= 0);
    assert(u < g->n);
    assert(v >= 0);
    assert(v < g->n);

    _graph_add_edge(g, u, v);
    _graph_set_edge_weight(g, u, v, wt);
}

/* return the number of vertices in the graph */
uint32
graph_vertex_count(Graph g)
{
    return g->n;
}

/* return the number of vertices in the graph */
uint32
graph_edge_count(Graph g)
{
    return g->m;
}

// [> return the out-degree of a vertex <]
// int
// graph_out_degree(Graph g, uint32 source)
// {
//     assert(source >= 0);
//     assert(source < g->n);

//     return g->alist[source]->d;
// }

// [> when we are willing to call bsearch <]
// #define BSEARCH_THRESHOLD (10)

// static int
// intcmp(const void *a, const void *b)
// {
//     return *((const uint32 *) a) - *((const uint32 *) b);
// }

// [> return 1 if edge (source, sink) exists), 0 otherwise <]
// int
// graph_has_edge(Graph g, uint32 source, uint32 sink)
// {
//     uint32 i;

//     assert(source >= 0);
//     assert(source < g->n);
//     assert(sink >= 0);
//     assert(sink < g->n);

//     if(graph_out_degree(g, source) >= BSEARCH_THRESHOLD) {
//         [> make sure it is sorted <]
//         if(! g->alist[source]->is_sorted) {
//             qsort(g->alist[source]->list,
//                     g->alist[source]->d,
//                     sizeof(int),
//                     intcmp);
//         }
        
//         [> call bsearch to do binary search for us <]
//         return 
//             bsearch(&sink,
//                     g->alist[source]->list,
//                     g->alist[source]->d,
//                     sizeof(int),
//                     intcmp)
//             != 0;
//     } else {
//         [> just do a simple linear search <]
//         [> we could call lfind for this, but why bother? <]
//         for(i = 0; i < g->alist[source]->d; i++) {
//             if(g->alist[source]->list[i] == sink) return 1;
//         }
//         [> else <]
//         return 0;
//     }
// }

/* invoke f on all edges (u,v) with source u */
/* supplying data as final parameter to f */
void
graph_foreach(Graph g, uint32 source,
    void (*f)(Graph g, uint32 source, uint32 sink, void *data),
    void *data)
{
    uint32 i = 0;
    struct vertex_t *v;

    assert(source < g->n);
    
    v = g->vertices[source];

    for(i = 0; i < v->adjs_num; i++) {
        f(g, source, v->adjs[i]->v->id, data);
    }
}

/* invoke f on all edges (u,v) with source u */
/* supplying data as final parameter to f */
void
graph_foreach_weighted(Graph g, int source,
    void (*f)(Graph g, int source, int sink, int weight, void *data),
    void *data)
{
    uint32 i = 0;
    struct vertex_t *v;

    assert(source >= 0);
    assert(source < g->n);

    v = g->vertices[source];

    for(i = 0; i < v->adjs_num; i++) {
        f(g, source, v->adjs[i]->v->id,
                     v->adjs[i]->w, data);
    }
}

void
graph_set_vertex_data(Graph g, uint32 v, void *data)
{
    if(NULL == g || v >= g->n || NULL == data)
        return;

    g->vertices[v]->data = data;
}

void*
graph_get_vertex_data(Graph g, uint32 v)
{
    if(NULL == g || v >= g->n)
        return NULL;

    return g->vertices[v]->data;
}

void
graph_dump_vertex(Graph g, uint32 v, char* buf, uint32 len)
{
    struct vertex_t *vertex = NULL;
    uint32 i = 0;
    uint32 consumed = 0;


    if(NULL == g || v >= g->n || NULL == buf || len == 0)
        return;

    vertex = g->vertices[v];

    for(i = 0; i < vertex->adjs_num; i++)
    {
        consumed = snprintf(buf, len, "(%u->%u) ", v,
                            vertex->adjs[i]->v->id);
        buf += consumed;
        len -= consumed;
    }

    return;
}
