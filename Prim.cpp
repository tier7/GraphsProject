#include "IGraph.h"
#include <climits>
#include "MinHeap.h"

int Prim(const IGraph& graph)
{
    const int INF = INT_MAX / 4;
    int vertexCount = graph.getVerticesCount();

    int* key = new int[vertexCount];
    bool* inTree = new bool[vertexCount]; // czy w mst

    int i;
    for (i = 0; i < vertexCount; i++) {
        key[i] = INF;
    }
    for (i = 0; i < vertexCount; i++) {
        inTree[i] = false;
    }

    key[0] = 0;

    int roughCap = vertexCount * vertexCount;
    MinHeap heap(roughCap);
    heap.push(0, 0);

    int totalWeight = 0;

    while (!heap.empty()) {
        HeapNode node = heap.popMin();
        int u = node.vertex;
        if (inTree[u]) {
            continue;
        }
        inTree[u] = true;
        totalWeight = totalWeight + node.key;

        int neighbourCount;
        Edge* neighbours = graph.getNeighbours(u, neighbourCount);

        int k;
        for (k = 0; k < neighbourCount; k++) {
            int v = neighbours[k].destination;
            int weight = neighbours[k].weight;
            // jesli v nie jest w MST i lepsza waga do kopca
            if (!inTree[v]) {
                if (weight < key[v]) {
                    key[v] = weight;
                    heap.push(key[v], v);
                }
            }
        }
        delete[] neighbours;
    }

    delete[] key;
    delete[] inTree;
    return totalWeight;
}
