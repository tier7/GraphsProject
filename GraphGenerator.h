#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "GraphType.h"
#include "IGraph.h"

// obliczanie ilosci krawedzi przy podanej gestosci grafu
inline int edgesCalculate(int v, float d, GraphType type) {
    if (type == UNDIRECTED) {
        return static_cast<int>(d * (v * (v - 1)) / 2);
    }
    else {
        return static_cast<int>(d * v * (v - 1));
    }
}

// generowanie losowego spojnego grafu
inline void generateGraph(IGraph& graph, float d, int minWeight, int maxWeight, GraphType t)
{

    int v = graph.getVerticesCount();

    int maxPossibleEdges = edgesCalculate(v, 1.0f, t);
    int requiredEdges = edgesCalculate(v, d, t);
    if (requiredEdges < v - 1) requiredEdges = v - 1;
    if (requiredEdges > maxPossibleEdges) requiredEdges = maxPossibleEdges;

    bool **edgeUsed = new bool*[v];
    for (int i = 0; i < v; ++i) {
        edgeUsed[i] = new bool[v];
        for (int j = 0; j < v; ++j) edgeUsed[i][j] = false;
    }

    int edgeCount = 0;

    // tworzenie spojnego lancucha
    for (int i = 0; i < v - 1; ++i) {
        int w = minWeight + rand() % (maxWeight - minWeight + 1);
        graph.addEdge(i, i + 1, w);
        edgeUsed[i][i+1] = true;
        if (t == UNDIRECTED) {
            edgeUsed[i+1][i] = true;
        }
        else {
            w = minWeight + rand() % (maxWeight - minWeight + 1);
            graph.addEdge(i+1, i, w);
            edgeUsed[i+1][i] = true;
        }
        ++edgeCount;
    }

    // tworzenie tablicy dostepnych krawedzi
    int pairsCount = 0;
    int* from = new int[maxPossibleEdges];
    int* to = new int[maxPossibleEdges];

    if (t == UNDIRECTED) {
        for (int i = 0; i < v; ++i) {
            for (int j = i+1; j < v; ++j) {
                if (!edgeUsed[i][j]) {
                    from[pairsCount] = i;
                    to[pairsCount]= j;
                    ++pairsCount;
                }
            }
        }
    } else {
        for (int i = 0; i < v; ++i) {
            for (int j = 0; j < v; ++j) {
                if (i != j && !edgeUsed[i][j]) {
                    from[pairsCount] = i;
                    to[pairsCount] = j;
                    ++pairsCount;
                }
            }
        }
    }

    // losowanie potecjalnych par
    for (int i = pairsCount - 1; i > 0; --i) {
        int swapWith = rand() % (i + 1);
        std::swap(from[i],from[swapWith]);
        std::swap(to[i], to[swapWith]);
    }

    // uzupelnianie grafu o brakujace krawedzie
    int edgesToAdd = requiredEdges - (v - 1);
    for (int i = 0; i < edgesToAdd && i < pairsCount; ++i) {
        int a = from[i];
        int b = to[i];
        int w = minWeight + rand() % (maxWeight - minWeight + 1);
        graph.addEdge(a, b, w);
        if (t == UNDIRECTED) edgeUsed[a][b] = edgeUsed[b][a] = true;
        else {
            edgeUsed[a][b] = true;
        }
    }

    for (int i = 0; i < v; ++i) delete[] edgeUsed[i];
    delete[] edgeUsed;
    delete[] from;
    delete[] to;
}


#endif
