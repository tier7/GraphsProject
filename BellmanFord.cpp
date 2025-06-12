
//
// Created by wiktor on 11.05.2025.
//

#include "BellmanFord.h"
#include <climits>

int *BellmanFord(const IGraph& graph, int start) {
    int v = graph.getVerticesCount();
    int ec;
    Edge* edges = graph.getEdges(ec);
    int* distance = new int[v];
    // inicjalizacja odleglosci
    for (int i = 0; i < v; i++) {
        distance[i] = INT_MAX;
    }
    if (start >= v || start < 0) {
        delete[] distance;
        delete[] edges;
        return nullptr;
    }
    distance[start] = 0;

    //glowna petla
    for (int i = 0; i < v-1; i++) {
        for (int j = 0; j < ec; j++) {
            int u = edges[j].from;
            int v = edges[j].destination;
            int w = edges[j].weight;
            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
            }
        }

    }
    // petla weryfikujaca
    for (int k = 0; k < ec; k++) {
        int u = edges[k].from;
        int v = edges[k].destination;
        int w = edges[k].weight;
        if (distance[u] + w < distance[v] && distance[u] != INT_MAX) {
            delete[] distance;
            delete[] edges;
            return nullptr;
        }
    }
    return distance;
}
