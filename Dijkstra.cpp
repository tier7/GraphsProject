//
// Created by wiktor on 11.05.2025.
//

#include "Dijkstra.h"
#include <climits>
#include "MinHeap.h"

int* Dijkstra(const IGraph& graph, int startVertex)
{
    const int INF = INT_MAX / 4;
    int vertexCount = graph.getVerticesCount();

    int* dist = new int[vertexCount];
    bool* visited = new bool[vertexCount];

    int i;
    // inicjalizacja odleglosci domyslnie wszystkie inf
    for (i = 0; i < vertexCount; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[startVertex] = 0;

    MinHeap heap(vertexCount*2, vertexCount);
    heap.push(0, startVertex);

    // glowna petla algorytmu
    while (!heap.empty()) {
        HeapNode node = heap.popMin();
        int u = node.vertex;
        if (visited[u]) continue;
        visited[u] = true;

        int n;
        Edge* neighbors = graph.getNeighbours(u, n);

        for (int k = 0; k < n; ++k) {
            int v = neighbors[k].destination;
            int w = neighbors[k].weight;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                heap.push(dist[v], v);
            }
        }
        delete[] neighbors;
    }


    delete[] visited;
    return dist;
}