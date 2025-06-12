//
// Created by wiktor on 11.05.2025.
//

#include "Dijkstra.h"
#include <climits>
#include "MinHeap.h"

int* Dijkstra(const IGraph& graph, int startVertex)
{
    const int INF = INT_MAX / 4; // inf zabezpieczenie przy dodawaniu
    int vertexCount = graph.getVerticesCount();

    int* dist = new int[vertexCount];
    bool* visited = new bool[vertexCount];

    int i;
    // inicjalizacja odleglosci domyslnie wszystkie inf
    for (i = 0; i < vertexCount; i++) {
        dist[i] = INF;
    }
    // inicjalizacja stanu przetworzenia wierzcholkow domyslnie false
    for (i = 0; i < vertexCount; i++) {
        visited[i] = false;
    }

    dist[startVertex] = 0;

    int roughCap = vertexCount * vertexCount;
    MinHeap heap(roughCap);
    heap.push(0, startVertex);

    // glowna petla algorytmu
    while (!heap.empty()) {
        HeapNode node = heap.popMin();
        int u = node.vertex;
        // pomijanie juz odwiedzonych wierzcholkow
        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        int neighbourCount;
        Edge* neighbours = graph.getNeighbours(u, neighbourCount);

        // relaksacja
        for (int k = 0; k < neighbourCount; k++) {
            int v = neighbours[k].destination;
            int weight = neighbours[k].weight;

            if (!visited[v]) {
                // aktualizacja jesli znaleziono krotsza sciezke
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    heap.push(dist[v], v);
                }
            }
        }
        delete[] neighbours;
    }

    delete[] visited;
    return dist;
}