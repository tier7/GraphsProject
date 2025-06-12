//
// Created by wiktor on 21.04.2025.
//

#ifndef LISTGRAPH_H
#define LISTGRAPH_H
#include "Edge.h"
#include "GraphType.h"
#include "IGraph.h"

class ListGraph : public IGraph {
public:
    ListGraph(int v, GraphType t);
    ~ListGraph();
    void addEdge(int a, int b, int weight);
    void removeEdge(int a, int b);
    Edge *getEdges(int &edgeCount) const;
    void print();
    int getVerticesCount() const;
    int getWeight(int u, int v) const override;
    GraphType getGraphType() const;
    Edge* getNeighbours(int u, int& n) const override;


private:
    struct ListEdge {
        int destination;
        int weight;
        ListEdge* next;
    };
    ListEdge** list;
    int vertices_count;
    GraphType graph_type;
};



#endif //LISTGRAPH_H
