#pragma once

#ifndef _GRAPH_H_
#define _GRAPH_H_ 1

#include <stdbool.h>

#include "struct/list.h"

typedef struct Graph Graph;
typedef struct Vertex Vertex;
typedef struct Edge Edge;


typedef void (*EdgeProcessor) (Graph *, Edge *, void *);
typedef void (*VertexProcessor) (Graph *, Vertex *, void *);
typedef void (*DualProcessor) (Graph *, Vertex *, Edge *, void *);

Graph *graph_new(bool);
void graph_destroy(Graph *);
bool graph_areAdjacent(const Graph *, const Vertex *, const Vertex *);
List *graph_vertices(const Graph *);
size_t graph_nVertices(const Graph *);
List *graph_edges(const Graph *);
size_t graph_nEdges(const Graph *);
bool graph_containsCycles(const Graph *);
bool graph_isDirected(const Graph *);
void graph_forEachVertex(Graph *, VertexProcessor, void *);
void graph_forEachEdge(Graph *, EdgeProcessor, void *);
Vertex *graph_getRandVertex(const Graph *);

Vertex *graph_newVertex(Graph *, void *);
void *graph_removeVertex(Graph *, Vertex *);

Vertex *vertex_opposite(const Vertex *, const Edge *);
void *vertex_getValue(const Vertex *);
void *vertex_setValue(Vertex *, void *);
void *vertex_getAlgData(const Vertex *);
void *vertex_setAlgData(Vertex *, void *);
List *vertex_incidentEdges(const Graph *, const Vertex *);
List *vertex_inEdges(const Graph *, const Vertex *);
List *vertex_outEdges(const Graph *, const Vertex *);
size_t vertex_getDegree(const Graph *, const Vertex *);
size_t vertex_getInDegree(const Graph *, const Vertex *);
size_t vertex_getOutDegree(const Graph *, const Vertex *);


Edge *graph_newEdge(Graph *, Vertex *, Vertex *, void *);
void *graph_removeEdge(Graph *, Edge *);

Vertex **edge_endVertices(const Edge *);
void *edge_getValue(const Edge *);
void *edge_setValue(Edge *, void *);
void *edge_getAlgData(const Edge *);
void *edge_setAlgData(Edge *, void *);
bool edge_isIncident(const Graph *, const Edge *, const Vertex *);

#endif /* ifndef _GRAPH_H_ */
