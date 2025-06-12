//
// Created by wiktor on 21.04.2025.
//

#include "Kruskal.h"

#include <iostream>
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "Sorter.h"

int findUltParent(int node, int* parent) {
    if (node==parent[node]) {
        return node;
    }
    return parent[node] = findUltParent(parent[node], parent);
}

// laczenie dwoch zbiorow
void unionByRank(int node1, int node2, int* rank, int* parent) {
    int uParent_node1 = findUltParent(node1, parent);
    int uParent_node2 = findUltParent(node2, parent);
    if (uParent_node1 == uParent_node2) {
        return;
    }
    // dodawanie mniejszego zbioru do wiekszego
    if (rank[uParent_node1] > rank[uParent_node2]) {
        parent[uParent_node2] = uParent_node1;
    }
    else if (rank[uParent_node1] < rank[uParent_node2]) {
        parent[uParent_node1] = uParent_node2;
    }
    else {
        parent[uParent_node2] = uParent_node1;
        rank[uParent_node1]++;
    }
}

int Kruskal(const IGraph &graph) {

    int edgeCount = 0;
    Edge* edges = graph.getEdges(edgeCount);
    sort(edges, edgeCount); // sortowanie rosnaco wedlug wag
    int vertices_count = graph.getVerticesCount();
    int* rank = new int[vertices_count];
    int* parent = new int[vertices_count];
    for (int i = 0; i < vertices_count; i++) {
        rank[i] = 0;
        parent[i] = i;
    }
    int weightSum = 0, edgesMST = 0;
    // przejscie po krawedziach jezeli u i v sa w innych zbiorach - dolaczamy
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].from;
        int v = edges[i].destination;
        if (findUltParent(u, parent) != findUltParent(v, parent)) {
            unionByRank(u, v, rank, parent);
            weightSum += edges[i].weight;
            edgesMST ++;
        }
    }
    // niespojny graf
    if (edgesMST < vertices_count-1) {
        weightSum = -1;
    }

    delete[] parent;
    delete[] rank;
    delete[] edges;
    return weightSum;
}



