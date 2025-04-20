//
// Created by wiktor on 21.04.2025.
//

#include "ListGraph.h"

ListGraph::ListGraph(int v, GraphType t) {
    vertices_count = v;
    graph_type = t;
    list = new int*[vertices_count];
}
}
