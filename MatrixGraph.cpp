//
// Created by wiktor on 20.04.2025.
//

#include "MatrixGraph.h"

#include <iostream>

#include "Edge.h"

MatrixGraph::MatrixGraph(int v, GraphType t) {
    vertices_count = v;
    graph_type = t;
    matrix = new int*[vertices_count];
    for (int i = 0; i < vertices_count; i++) {
        matrix[i] = new int[vertices_count];
        for (int j = 0; j < vertices_count; j++) {
            matrix[i][j] = 0;
        }
    }
}

MatrixGraph::~MatrixGraph() {
    for (int i = 0; i < vertices_count; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void MatrixGraph::print() {
    for (int i = 0; i < vertices_count; i++) {
        for (int j = 0; j < vertices_count; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void MatrixGraph::addEdge(int a, int b, int weight) {
    if (a >= 0 && b >= 0 && a<=vertices_count && b<=vertices_count) {matrix[a][b] = weight;
        if (graph_type == UNDIRECTED) {
            matrix[b][a] = weight;
        }
    }
    else {
        std::cerr << "Edge index out of range" << std::endl;
    }
}


void MatrixGraph::removeEdge(int a, int b) {
    matrix[a][b] = 0;
    if (graph_type == UNDIRECTED) {
        matrix[b][a] = 0;
    }
}

Edge* MatrixGraph::getEdges(int &edgeCount) const {
    edgeCount = 0;
    Edge* edgeTab = new Edge[vertices_count*vertices_count];
    for (int i = 0; i < vertices_count; i++) {
        for (int j = 0; j < vertices_count; j++) {
            if (matrix[i][j] != 0) {
                edgeTab[edgeCount++] = {i,j,matrix[i][j]};
            }
        }
    }
    return edgeTab;
}

int MatrixGraph::getVerticesCount() const{
    return vertices_count;
}



