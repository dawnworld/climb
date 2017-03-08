/*
 * shortest_path.c
 * Copyright (C) 2017 dawnworld <thundon@qq.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdlib.h>
#include <assert.h>

#include "graph/shortest_path.h"

/* data field for relax helper */
struct relax_data {
    int improved;
    int *dist;
    int *parent;
};

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



