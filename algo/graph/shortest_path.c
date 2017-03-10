/*
 * shortest_path.c
 * Copyright (C) 2017 dawnworld <thundon@qq.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdlib.h>
#include <assert.h>

#include "graph/pq.h"
#include "graph/shortest_path.h"

/* data field for relax helper */
struct relax_data {
    int improved;
    int *dist;
    int *parent;
};

/* internal edge representation for dijkstra */
struct pq_elt {
    int d;      /* distance to v */
    int u;      /* source */
    int v;      /* sink */
};

static int
pq_elt_cmp(const void *a, const void *b)
{
    return ((const struct pq_elt *) a)->d - ((const struct pq_elt *) b)->d;
}

struct push_data {
    PQ pq;
    int *dist;
};

static void push(Graph g, int u, int v, int wt, void *data)
{
    struct push_data *d;
    struct pq_elt e;

    d = data;

    e.d = d->dist[u] + wt;
    e.u = u;
    e.v = v;

    pq_insert(d->pq, &e);
}

static void
relax(Graph g, int source, int sink, int weight, void *data)
{
    int len;
    struct relax_data *d;

    d = data;

    if(d->dist[source] < MAXINT && weight < MAXINT) {
        len = d->dist[source] + weight;

        if(len < d->dist[sink]) {
            d->dist[sink] = len;
            if(d->parent) d->parent[sink] = source;
            d->improved = 1;
        }
    }
}

/* returns 1 if there is a negative cycle */
int
bellman_ford(Graph g, int source, int *dist, int *parent)
{
    int round;
    int n;
    int i;
    struct relax_data d;

    assert(dist);

    d.dist = dist;
    d.parent = parent;
    d.improved = 1;

    n = graph_vertex_count(g);

    for(i = 0; i < n; i++) {
        d.dist[i] = MAXINT;
        if(d.parent) d.parent[i] = SHORTEST_PATH_NULL_PARENT;
    }

    d.dist[source] = 0;
    d.parent[source] = source;

    for(round = 0; d.improved && round < n; round++) {
        d.improved = 0;

        /* relax all edges */
        for(i = 0; i < n; i++) {
            graph_foreach_weighted(g, i, relax, &d);
        }
    }

    return d.improved;
}

void
dijkstra(Graph g, int source, int *dist, int *parent)
{
    struct push_data data;
    struct pq_elt e;
    int n;
    int i;

    assert(dist);

    data.dist = dist;
    data.pq = pq_create(sizeof(struct pq_elt), pq_elt_cmp);
    assert(data.pq);

    n = graph_vertex_count(g);

    /* set up dist and parent arrays */
    for(i = 0; i < n; i++) {
        dist[i] = MAXINT;
    }
        
    if(parent) {
        for(i = 0; i < n; i++) {
            parent[i] = DIJKSTRA_NULL_PARENT;
        }
    }

    /* push (source, source, 0) */
    /* this will get things started with parent[source] == source */
    /* and dist[source] == 0 */
    push(g, source, source, -MAXINT, &data);

    while(!pq_is_empty(data.pq)) {
        /* pull the min value out */
        pq_delete_min(data.pq, &e);

        /* did we reach the sink already? */
        if(dist[e.v] == MAXINT) {
            /* no, it's a new edge */
            dist[e.v] = e.d;
            if(parent) parent[e.v] = e.u;

            /* throw in the outgoing edges */
            graph_foreach_weighted(g, e.v, push, &data);
        }
    }

    pq_destroy(data.pq);
}

