//
// Created by wiktor on 21.04.2025.
//

#ifndef LISTGRAPH_H
#define LISTGRAPH_H
#include "Edge.h"

class ListGraph {
public:
    enum GraphType {
        DIRECTED,
        UNDIRECTED
    };
    ListGraph(int v, GraphType t);
    ~ListGraph();
    void addEdge(int a, int b, int weight);
    void removeEdge(int a, int b);
    Edge *getEdges(int &edgeCount) const;
    void print();

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
