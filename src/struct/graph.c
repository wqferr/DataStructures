#include <stdlib.h>
#include <stddef.h>

#include "struct/graph.h"
#include "struct/list.h"

struct Vertex {
    void *value;
    void *algData;
    List *adjacency;
};

struct Edge {
    Vertex *v1;
    Vertex *v2;

    void *value;
    void *algData;
    ListIterator *adjacency1;
    ListIterator *adjacency2;
};

struct Graph {
    List *vertices;
    List *edges;

    bool directed: 1;
};


Graph *graph_new(bool directed) {
    Graph *g = (Graph *) malloc(sizeof(*g));

    g->vertices = list_new();
    g->edges = list_new();

    g->directed = directed;

    return g;
}

void graph_destroy(Graph *g) {
    ListIterator *iter = list_iterator(g->vertices);
    Vertex *curr;

    (void) listiter_next(iter);
    while (listiter_hasCurr(iter)) {
        curr = listiter_curr(iter);
        (void) listiter_next(iter);
        (void) graph_removeVertex(g, (Vertex *) curr);
    }

    listiter_destroy(iter);
    list_destroy(g->vertices);
    list_destroy(g->edges);
    free(g);
}

List *graph_vertices(const Graph *g) {
    List *vertices = list_new();
    ListIterator *iter = list_iterator(g->vertices);

    while (listiter_hasNext(iter))
        list_append(vertices, listiter_next(iter));
    listiter_destroy(iter);

    return vertices;
}

size_t graph_nVertices(const Graph *g) {
    return list_length(g->vertices);
}

List *graph_edges(const Graph *g) {
    List *edges = list_new();
    ListIterator *iter = list_iterator(g->edges);

    while (listiter_hasNext(iter))
        list_append(edges, listiter_next(iter));
    listiter_destroy(iter);

    return edges;
}

size_t graph_nEdges(const Graph *g) {
    return list_length(g->edges);
}

void graph_forEachVertex(Graph *g, VertexProcessor proc, void *arg) {
    ListIterator *iter = list_iterator(g->vertices);

    while (listiter_hasNext(iter))
        proc(g, (Vertex *) listiter_next(iter), arg);

    listiter_destroy(iter);
}

void graph_forEachEdge(Graph *g, EdgeProcessor proc, void *arg) {
    ListIterator *iter = list_iterator(g->edges);

    while (listiter_hasNext(iter))
        proc(g, (Edge *) listiter_next(iter), arg);

    listiter_destroy(iter);
}

bool graph_isDirected(const Graph *g) {
    return g->directed;
}

Vertex *graph_newVertex(Graph *g, void *value) {
    Vertex *v = (Vertex *) malloc(sizeof(*v));

    v->adjacency = list_new();
    v->value = value;
    v->algData = NULL;

    list_append(g->vertices, v);

    return v;
}

size_t vertex_getDegree(const Graph *g, const Vertex *v) {
    (void) g;
    return list_length(v->adjacency);
}

size_t vertex_getInDegree(const Graph *g, const Vertex *v) {
    size_t deg = 0;
    ListIterator *iter = list_iterator(v->adjacency);
    Edge *e;
    (void) g;

    while (listiter_hasNext(iter)) {
        e = (Edge *) listiter_next(iter);
        if (e->v2 == v)
            deg++;
    }
    listiter_destroy(iter);

    return deg;
}

size_t vertex_getOutDegree(const Graph *g, const Vertex *v) {
    size_t deg = 0;
    ListIterator *iter = list_iterator(v->adjacency);
    Edge *e;
    (void) g;

    while (listiter_hasNext(iter)) {
        e = (Edge *) listiter_next(iter);
        if (e->v1 == v)
            deg++;
    }
    listiter_destroy(iter);

    return deg;
}

Vertex *vertex_opposite(const Vertex *v, const Edge *e) {
    return e->v1 == v ? e->v2 : e->v1;
}

void *vertex_getValue(const Vertex *v) {
    return v->value;
}

void *vertex_setValue(Vertex *v, void *value) {
    void *prevValue = v->value;
    v->value = value;
    return prevValue;
}

void *vertex_getAlgData(const Vertex *v) {
    return v->algData;
}

void *vertex_setAlgData(Vertex *v, void *value) {
    void *val = v->algData;
    v->algData = value;
    return val;
}

bool graph_areAdjacent(const Graph *g, const Vertex *v, const Vertex *w) {
    ListIterator *iter;
    const Vertex *this, *other;
    Edge *e;
    bool adj = false;
    (void) g;

    if (g->directed || list_length(v->adjacency) < list_length(w->adjacency)) {
        this = v;
        other = w;
        iter = list_iterator(v->adjacency);
    } else {
        this = w;
        other = v;
        iter = list_iterator(w->adjacency);
    }

    while (listiter_hasNext(iter) && !adj) {
        e = (Edge *) listiter_next(iter);
        if (vertex_opposite(this, e) == other)
            adj = !g->directed || e->v2 == other;
    }

    listiter_destroy(iter);
    return adj;
}

List *vertex_incidentEdges(const Graph *g, const Vertex *v) {
    List *edges = list_new();
    ListIterator *iter = list_iterator(v->adjacency);
    (void) g;

    while (listiter_hasNext(iter))
        list_append(edges, listiter_next(iter));

    listiter_destroy(iter);
    return edges;
}

List *vertex_inEdges(const Graph *g, const Vertex *v) {
    List *edges;
    ListIterator *iter;
    Edge *e;

    if (!g->directed)
        return vertex_incidentEdges(g, v);

    edges = list_new();
    iter = list_iterator(v->adjacency);

    while (listiter_hasNext(iter)) {
        e = listiter_next(iter);
        if (e->v2 == v)
            list_append(edges, e);
    }

    listiter_destroy(iter);
    return edges;
}

List *vertex_outEdges(const Graph *g, const Vertex *v) {
    List *edges;
    ListIterator *iter;
    Edge *e;

    if (!g->directed)
        return vertex_incidentEdges(g, v);

    edges = list_new();
    iter = list_iterator(v->adjacency);

    while (listiter_hasNext(iter)) {
        e = listiter_next(iter);
        if (e->v1 == v)
            list_append(edges, e);
    }

    listiter_destroy(iter);
    return edges;
}

void *graph_removeVertex(Graph *g, Vertex *v) {
    ListIterator *edges = list_iterator(v->adjacency);
    Edge *e;
    void *value = v->value;
    (void) listiter_next(edges);

    while (listiter_hasCurr(edges)) {
        e = (Edge *) listiter_curr(edges);
        (void) listiter_next(edges);
        (void) graph_removeEdge(g, e);
    }

    listiter_destroy(edges);
    list_destroy(v->adjacency);
    (void) list_remove(g->vertices, v);
    free(v);
    return value;
}

Vertex *graph_getRandVertex(const Graph *g) {
    return list_getFirst(g->vertices);
}


Edge *graph_newEdge(Graph *g, Vertex *v, Vertex *w, void *value) {
    Edge *e = (Edge *) malloc(sizeof(*e));

    e->v1 = v;
    e->v2 = w;
    e->value = value;
    e->algData = NULL;

    list_append(g->edges, e);

    list_append(v->adjacency, e);
    list_append(w->adjacency, e);

    e->adjacency1 = list_iterator(v->adjacency);
    (void) listiter_prev(e->adjacency1);
    e->adjacency2 = list_iterator(w->adjacency);
    (void) listiter_prev(e->adjacency2);

    return e;
}

Vertex **edge_endVertices(const Edge *e) {
    Vertex **vertices = (Vertex **) malloc(2 * sizeof(*vertices));

    vertices[0] = e->v1;
    vertices[1] = e->v2;

    return vertices;
}

void *edge_getValue(const Edge *e) {
    return e->value;
}

void *edge_setValue(Edge *e, void *value) {
    void *prevValue = e->value;
    e->value = value;
    return prevValue;
}

void *edge_getAlgData(const Edge *e) {
    return e->algData;
}

void *edge_setAlgData(Edge *e, void *value) {
    void *val = e->algData;
    e->algData = value;
    return val;
}

bool edge_isIncident(const Graph *g, const Edge *e, const Vertex *v) {
    (void) g;
    return (e->v1 == v) || (e->v2 == v);
}

void *graph_removeEdge(Graph *g, Edge *e) {
    void *value = e->value;
    (void) g;

    (void) listiter_remove(e->adjacency1);
    (void) listiter_remove(e->adjacency2);
    listiter_destroy(e->adjacency1);
    listiter_destroy(e->adjacency2);
    (void) list_remove(g->edges, e);
    free(e);
    return value;
}
