//
// Created by wiktor on 21.04.2025.
//

#include "ListGraph.h"
#include <iostream>

struct Edge {
    int destination;
    int weight;
    Edge *next;
};

ListGraph::ListGraph(int v, GraphType t) {
    vertices_count = v;
    graph_type = t;
    list = new Edge *[vertices_count];
    for (int i = 0; i < vertices_count; i++) {
        list[i] = nullptr;
    }
}

ListGraph::~ListGraph() {
    for (int i = 0; i < vertices_count; i++) {
        delete[] list[i];
    }
    delete[] list;
}

void ListGraph::print() {
    for (int i = 0; i < vertices_count; i++) {
        std::cout << i << ": ";
        Edge *current_edge = list[i];
        while (current_edge != nullptr) {
            std::cout << current_edge->destination << "(" << current_edge->weight << ")->";
            current_edge = current_edge->next;
        }
        std::cout << "nullptr\n";
    }
}

void ListGraph::addEdge(int a, int b, int w) {
    Edge *edge = new Edge;
    edge->destination = b;
    edge->weight = w;
    edge->next = list[a];
    list[a] = edge;
    if (graph_type == UNDIRECTED) {
        Edge *reverse_edge = new Edge;
        reverse_edge->destination = a;
        reverse_edge->weight = w;
        reverse_edge->next = list[b];
        list[b] = reverse_edge;
    }
}

void ListGraph::removeEdge(int a, int b) {
    Edge *current_edge = list[a];
    Edge *prev_edge = nullptr;
    while (current_edge != nullptr) {
        if (current_edge->destination == b) {
            if (prev_edge == nullptr) {
                list[a] = current_edge->next;
            }
            else {
                prev_edge->next = current_edge->next;
            }
            delete current_edge;
            break;
        }
        prev_edge = current_edge;
        current_edge = current_edge->next;
    }
    if (graph_type == UNDIRECTED) {
        Edge *current_edge = list[b];
        Edge *prev_edge = nullptr;
        while (current_edge != nullptr) {
            if (current_edge->destination == a) {
                if (prev_edge == nullptr) {
                    list[b] = current_edge->next;
                }
                else {
                    prev_edge->next = current_edge->next;
                }
            }
            prev_edge = current_edge;
            current_edge = current_edge->next;
        }
    }
}
