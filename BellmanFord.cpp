
//
// Created by wiktor on 11.05.2025.
//

#include "BellmanFord.h"
#include <climits>

int *BellmanFord(const IGraph& graph, int start) {
    int v = graph.getVerticesCount();
    int ec;
    int INF = INT_MAX/4;
    Edge* edges = graph.getEdges(ec);
    int* distance = new int[v];
    // inicjalizacja odleglosci
    for (int i = 0; i < v; i++) {
        distance[i] = INF;
    }
    if (start >= v || start < 0) {
        delete[] distance;
        delete[] edges;
        return nullptr;
    }
    distance[start] = 0;

    //glowna petla
    for (int i = 0; i < v-1; i++) {
        //bool changed = false;
        for (int j = 0; j < ec; j++) {
            int u = edges[j].from;
            int v = edges[j].destination;
            int w = edges[j].weight;
            if (distance[u] != INF && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                //changed = true;
            }
        }
        /*if (!changed) {
            break;
        }*/


    }
    // petla weryfikujaca
    for (int k = 0; k < ec; k++) {
        int u = edges[k].from;
        int v = edges[k].destination;
        int w = edges[k].weight;
        if (distance[u] + w < distance[v] && distance[u] != INF) {
            delete[] distance;
            delete[] edges;
            return nullptr;
        }
    }
    return distance;
}
