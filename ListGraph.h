//
// Created by wiktor on 21.04.2025.
//

#ifndef LISTGRAPH_H
#define LISTGRAPH_H


class ListGraph {
public:
    enum GraphType {
        DIRECTED,
        UNDIRECTED
    };
    ListGraph(int v, GraphType t);
    ~ListGraph();
    void addEdge(int a, int b, int weight, int next);
    void removeEdge(int a, int b);
    void print();

private:
    struct Edge {
        int destination;
        int weight;
        Edge* next;
    };
    Edge** list;
    int vertices_count;
    GraphType graph_type;
};



#endif //LISTGRAPH_H
