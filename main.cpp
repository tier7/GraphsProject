#include <iostream>
#include "ListGraph.h"

int main() {
    ListGraph g(5, ListGraph::GraphType::UNDIRECTED);
    g.addEdge(0,1,5);
    g.addEdge(1,2,6);
    g.addEdge(1,3,7);
    g.print();
    g.removeEdge(0,1);
    g.print();
}