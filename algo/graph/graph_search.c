/*
 * graph_search.c
 * Copyright (C) 2017 dawnworld <thundon@qq.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <assert.h>

#include "graph/graph_search.h"


/* create an array of n ints initialized to SEARCH_INFO_NULL */
static int *
create_empty_array(int n)
{
    int *a;
    int i;

    a = MALLOC(sizeof(*a) * n);
    assert(a);

    for(i = 0; i < n; i++) {
        a[i] = SEARCH_INFO_NULL;
    }

    return a;
}

/* allocate and initialize search results structure */
/* you need to do this before passing it to dfs or bfs */
struct search_info *
search_info_create(Graph g)
{
    struct search_info *s;
    int n;

    s = MALLOC(sizeof(*s));
    assert(s);

    s->graph = g;
    s->reached = 0;

    n = graph_vertex_count(g);

    s->preorder = create_empty_array(n);
    s->time = create_empty_array(n);
    s->parent = create_empty_array(n);
    s->depth = create_empty_array(n);

    return s;
}

void
search_info_reset(struct search_info *s)
{
    uint32 i = 0;
    uint32 n = 0;

    if(NULL == s || NULL == s->graph)
        return;

    s->reached = 0;
    n = graph_vertex_count(s->graph);

    for(i = 0; i < n; i++) {
        s->preorder[i] = SEARCH_INFO_NULL;
        s->time[i] = SEARCH_INFO_NULL;
        s->parent[i] = SEARCH_INFO_NULL;
        s->depth[i] = SEARCH_INFO_NULL;
    }
}

/* FREE search_info data---does NOT FREE graph pointer */
void
search_info_destroy(struct search_info *s)
{
    FREE(s->depth);
    FREE(s->parent);
    FREE(s->time);
    FREE(s->preorder);
    FREE(s);
}

/* used inside search routines */
struct edge {
    int u;          /* source */
    int v;          /* sink */
};

/* stack/queue */
struct queue {
    struct edge *e;
    int bottom;
    int top;
};

static void
push_edge(Graph g, uint32 u, uint32 v, void *data)
{
    struct queue *q;

    q = data;

    assert(q->top < graph_edge_count(g) + 1);

    q->e[q->top].u = u;
    q->e[q->top].v = v;
    q->top++;
}

/* this rather horrible function implements dfs if use_queue == 0 */
/* and bfs if use_queue == 1 */
static void
generic_search(struct search_info *r, int root, int use_queue)
{
    /* queue/stack */
    struct queue q;

    /* edge we are working on */
    struct edge cur;

    /* start with empty q */
    /* we need one space per edge */
    /* plus one for the fake (root, root) edge */
    q.e = MALLOC(sizeof(*q.e) * (graph_edge_count(r->graph) + 1));
    assert(q.e);

    q.bottom = q.top = 0;

    /* push the root */
    push_edge(r->graph, root, root, &q);

    /* while q.e not empty */
    while(q.bottom < q.top) {
        if(use_queue) {
            cur = q.e[q.bottom++];
        } else {
            cur = q.e[--q.top];
        }

        /* did we visit sink already? */
        if(r->parent[cur.v] != SEARCH_INFO_NULL) continue;

        /* no */
        assert(r->reached < graph_vertex_count(r->graph));
        r->parent[cur.v] = cur.u;
        r->time[cur.v] = r->reached;
        r->preorder[r->reached++] = cur.v;
        if(cur.u == cur.v) {
            /* we could avoid this if we were certain SEARCH_INFO_NULL */
            /* would never be anything but -1 */
            r->depth[cur.v] = 0;
        } else {
            r->depth[cur.v] = r->depth[cur.u] + 1;
        }

        /* push all outgoing edges */
        graph_foreach(r->graph, cur.v, push_edge, &q);
    }

    FREE(q.e);
}

void
dfs(struct search_info *results, uint32 root)
{
    generic_search(results, root, 0);
}

void
bfs(struct search_info *results, uint32 root)
{
    generic_search(results, root, 1);
}
