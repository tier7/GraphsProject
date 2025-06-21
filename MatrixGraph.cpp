//
// Created by wiktor on 20.04.2025.
//

#include "MatrixGraph.h"

#include <iostream>

#include "Edge.h"

MatrixGraph::MatrixGraph(int v, int maxE, GraphType t) {
    vertices_count = v;
    max_edges = maxE;
    edges_count = 0;
    graph_type = t;
    //tworzenie macierzy incydencji
    incidence = new int*[vertices_count];
    for(int i = 0; i < vertices_count; i++) {
        incidence[i] = new int[max_edges];
        for(int j = 0; j < max_edges; j++)
            incidence[i][j] = 0;
    }
    edgeFrom = new int[max_edges];
    edgeTo = new int[max_edges];
    weights = new int[max_edges];
}

MatrixGraph::~MatrixGraph() {
    for (int i = 0; i < vertices_count; i++) {
        delete[] incidence[i];
    }
    delete[] incidence;
    delete[] edgeFrom;
    delete[] edgeTo;
    delete[] weights;
}

void MatrixGraph::print() {
    for (int i = 0; i < vertices_count; i++) {
        for (int j = 0; j < edges_count; j++) {
            std::cout << incidence[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void MatrixGraph::addEdge(int u, int v, int w) {
    if(edges_count >= max_edges) return;
    // dla skierowanych -1 = incydencja ujemna
    if(graph_type == UNDIRECTED) {
        incidence[u][edges_count] = 1;
        incidence[v][edges_count] = 1;
    } else {
        incidence[u][edges_count] = 1;
        incidence[v][edges_count] = -1;
    }
    edgeFrom[edges_count] = u;
    edgeTo[edges_count] = v;
    weights[edges_count] = w;
    edges_count++;
}


void MatrixGraph::removeEdge(int a, int b) {
    for (int e = 0; e < edges_count; ++e) {
        if ( (graph_type == UNDIRECTED && ((edgeFrom[e] == a && edgeTo[e] == b) || (edgeFrom[e] == b && edgeTo[e] == a)) || (graph_type == DIRECTED && edgeFrom[e] == a && edgeTo[e] == b) ))
            {
            for (int i = 0; i < vertices_count; ++i) {
                incidence[i][e] = 0;
            }
            edgeFrom[e] = -1;
            edgeTo[e] = -1;
            weights[e] = 0;
            }
    }
}


Edge* MatrixGraph::getEdges(int &edgeCount) const {
    edgeCount = 0;
    Edge* edgeTab = new Edge[edges_count];
    for (int e = 0; e < edges_count; ++e) {
        if (edgeFrom[e] != -1 && edgeTo[e] != -1) {
            edgeTab[edgeCount++] = {edgeFrom[e], edgeTo[e], weights[e]};
        }
    }
    return edgeTab;
}



int MatrixGraph::getVerticesCount() const{
    return vertices_count;
}

GraphType MatrixGraph::getGraphType() const{
    return graph_type;
}

int MatrixGraph::getWeight(int u, int v) const {
    for(int e = 0; e < edges_count; e++) {
        if(graph_type == UNDIRECTED) {
            if((edgeFrom[e] == u && edgeTo[e] == v) ||
               (edgeFrom[e] == v && edgeTo[e] == u)) {
                return weights[e];
               }
        } else {
            if(edgeFrom[e] == u && edgeTo[e] == v)
                return weights[e];
        }
    }
    return 0;
}


Edge* MatrixGraph::getNeighbours(int u, int& n) const {
    n = 0;
    Edge* results = new Edge[edges_count];

    for (int e = 0; e < edges_count; e++) {
        if (edgeFrom[e] == -1) continue;
        if (graph_type == DIRECTED) {
            if (edgeFrom[e] == u) {
                results[n] = {u, edgeTo[e], weights[e]};
                n++;
            }
        } else {
            if (incidence[u][e] != 0) {
                int other = (edgeFrom[e] == u) ? edgeTo[e] : edgeFrom[e];
                results[n] = {u, other, weights[e]};
                n++;
            }
        }
    }
    return results;
}




