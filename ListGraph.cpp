//
// Created by wiktor on 21.04.2025.
//

#include "ListGraph.h"
#include <iostream>

struct ListEdge {
    int destination;
    int weight;
    ListEdge* next;
};

ListGraph::ListGraph(int v, GraphType t) {
    vertices_count = v;
    graph_type = t;
    list = new ListEdge *[vertices_count];
    for (int i = 0; i < vertices_count; i++) {
        list[i] = nullptr;
    }
}

ListGraph::~ListGraph() {
    // kasowanie kazdej listy sasiedztwa
    for (int i = 0; i < vertices_count; i++) {
        ListEdge* curr_edge = list[i];
        while (curr_edge != nullptr) {
            ListEdge* del_edge = curr_edge;
            curr_edge = curr_edge->next;
            delete del_edge;
        }
    }
    delete[] list;
}
// wypisanie grafu
void ListGraph::print() {
    for (int i = 0; i < vertices_count; i++) {
        std::cout << i << ": ";
        ListEdge *current_edge = list[i];
        while (current_edge != nullptr) {
            std::cout << current_edge->destination << "(" << current_edge->weight << ")->";
            current_edge = current_edge->next;
        }
        std::cout << "nullptr\n";
    }
}
// dodanie nowej krawedzi do grafu
void ListGraph::addEdge(int a, int b, int w) {
    ListEdge *edge = new ListEdge;
    edge->destination = b;
    edge->weight = w;
    edge->next = list[a];
    list[a] = edge;
    if (graph_type == UNDIRECTED) {
        ListEdge *reverse_edge = new ListEdge;
        reverse_edge->destination = a;
        reverse_edge->weight = w;
        reverse_edge->next = list[b];
        list[b] = reverse_edge;
    }
}
// usuwanie wybranej krawedzi
void ListGraph::removeEdge(int a, int b) {
    ListEdge *current_edge = list[a];
    ListEdge *prev_edge = nullptr;
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
    // dla grafu nieskierowanego usunac tez w druga strone
    if (graph_type == UNDIRECTED) {
        ListEdge *current_edge = list[b];
        ListEdge *prev_edge = nullptr;
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
Edge* ListGraph::getEdges(int &edgeCount) const {
    edgeCount = 0;
    Edge* edgeTab = new Edge[vertices_count*vertices_count];
    for (int i = 0; i < vertices_count; i++) {
        ListEdge *current_edge = list[i];
        while (current_edge != nullptr) {
            if (graph_type == UNDIRECTED && current_edge->destination > i) {
                edgeTab[edgeCount] = {i, current_edge->destination, current_edge->weight};
                edgeCount++;
            }
            else if (graph_type == DIRECTED) {
                edgeTab[edgeCount] = {i, current_edge->destination, current_edge->weight};
                edgeCount++;
            }
            current_edge = current_edge->next;

        }

    }
    return edgeTab;
}

int ListGraph::getVerticesCount() const{
    return vertices_count;
}

GraphType ListGraph::getGraphType() const{
    return graph_type;
}

int ListGraph::getWeight(int u, int v) const {
    ListEdge* c = list[u];
    int minWeight = INT_MAX;
    bool found = false;
    while (c != nullptr) {
        if (c->destination == v) {
            found = true;
            if (minWeight > c->weight) {
                minWeight = c->weight;
            }
        }
        c = c->next;
    }
    if (found == true) {
        return minWeight;
    }
    else {
        return 0;
    }
}

Edge* ListGraph::getNeighbours(int u, int& cnt) const {
    cnt = 0;
    ListEdge* curr = list[u];
    while (curr != nullptr) {
        cnt++;
        curr = curr->next;
    }

    Edge* result = new Edge[cnt];
    curr = list[u];
    for (int i = 0; i < cnt; ++i) {
        result[i] = {u, curr->destination, curr->weight};
        curr = curr->next;
    }
    return result;
}

