//
// Created by wiktor on 21.04.2025.
//

#include "Kruskal.h"
#include "MatrixGraph.h"
#include "Sorter.h"

int findUltParent(int node, int* parent) {
    if (node==parent[node]) {
        return node;
    }
    return parent[node] = findUltParent(parent[node], parent);
}

void unionByRank(int node1, int node2, int* rank, int* parent) {
    int uParent_node1 = findUltParent(node1, parent);
    int uParent_node2 = findUltParent(node2, parent);
    if (uParent_node1 == uParent_node2) {
        return;
    }
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

int Kruskal::KruskalMatrix(const MatrixGraph &graph) {

    int edgeCount = 0;
    Edge* edges = graph.getEdges(edgeCount);
    sort(edges, edgeCount);
    int vertices_count = graph.getVerticesCount();
    int* rank = new int[vertices_count];
    int* parent = new int[vertices_count];
    for (int i = 0; i < vertices_count; i++) {
        rank[i] = 0;
        parent[i] = i;
    }
    int weightSum = 0, edgesMST = 0;
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].from;
        int v = edges[i].destination;
        if (findUltParent(u, parent) != findUltParent(v, parent)) {
            unionByRank(u, v, rank, parent);
            weightSum += edges[i].weight;
            edgesMST ++;
        }
    }
    delete[] parent;
    delete[] rank;
    delete[] edges;
    return weightSum;

}
