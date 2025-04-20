<<<<<<< HEAD
//
// Created by wiktor on 20.04.2025.
//

#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H



class MatrixGraph {
public:
    enum GraphType {
        DIRECTED,
        UNDIRECTED
    };
    MatrixGraph(int v, GraphType t);
    ~MatrixGraph();
    void addEdge(int a, int b, int weight);
    void removeEdge(int a, int b);
    void print();

private:
    int** matrix;
    int vertices_count;
    GraphType graph_type;
};


#endif //MATRIXGRAPH_H
=======
//
// Created by wiktor on 20.04.2025.
//

#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H



class MatrixGraph {
public:
    enum GraphType {
        DIRECTED,
        UNDIRECTED
    };
    MatrixGraph(int v, GraphType t);
    ~MatrixGraph();
    void addEdge(int a, int b, int weight);
    void removeEdge(int a, int b);
    void print();

private:
    int** matrix;
    int vertices_count;
    GraphType graph_type;
};


#endif //MATRIXGRAPH_H
>>>>>>> 6f22666 (Matrix Graph implementation and beginning of List Graph)
