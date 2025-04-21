//
// Created by wiktor on 21.04.2025.
//

#include "Kruskal.h"
#include "MatrixGraph.h"
#include "Sorter.h"

void Kruskal::KruskalMatrix(const MatrixGraph &graph) {
    int edgeCount = 0;
    Edge* edges = graph.getEdges(edgeCount);
    sort(edges, edgeCount);
    int vertices_count = graph.getVerticesCount();
    int *rank = new int[vertices_count];
    int* parent = new int[vertices_count];
}
