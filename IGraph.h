//
// Created by wiktor on 02.05.2025.
//

#ifndef IGRAPH_H
#define IGRAPH_H
#include "Edge.h"
#include "GraphType.h"


// interfejs dla reprezentacji grafu
class IGraph {
public:
    virtual ~IGraph() {}

    virtual void addEdge(int u, int v, int w) = 0;
    virtual void removeEdge(int u, int v)= 0;
    virtual Edge* getEdges(int& edgeCount) const= 0;
    virtual int getVerticesCount() const= 0;
    virtual void print()= 0;
    virtual int getWeight(int u, int v) const= 0;
    virtual GraphType getGraphType() const= 0;
    virtual Edge* getNeighbours(int u, int& n) const = 0;


};



#endif //IGRAPH_H
