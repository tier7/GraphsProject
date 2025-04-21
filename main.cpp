#include <iostream>
#include "ListGraph.h"
#include "Kruskal.h"

int main() {
    MatrixGraph g(7, MatrixGraph::UNDIRECTED);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);
    Kruskal k;
    std::cout<<k.KruskalMatrix(g)<<std::endl;
    g.print();
}