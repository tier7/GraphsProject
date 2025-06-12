//
// Created by wiktor on 20.04.2025.
//

#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include "Edge.h"
#include "GraphType.h"
#include "IGraph.h"


class MatrixGraph : public IGraph {
    int vertices_count;
    int max_edges;
    int edges_count;
    int** incidence;
    int* edgeFrom;
    int* edgeTo;
    int* weights;
    GraphType graph_type;
public:
    MatrixGraph(int v, int maxE, GraphType t);
    ~MatrixGraph();
    void addEdge(int u, int v, int w) override;
    void removeEdge(int u, int v) override;
    void print() override;
    int getVerticesCount() const override;
    GraphType getGraphType() const override;
    int getWeight(int u, int v) const override;
    Edge* getNeighbours(int u, int& n) const override;
    Edge* getEdges(int& edgeCount) const override;
};


#endif //MATRIXGRAPH_H
