cmake_minimum_required(VERSION 3.30)
project(GraphsProject)

set(CMAKE_CXX_STANDARD 23)

add_executable(GraphsProject
        main.cpp
        MatrixGraph.cpp
        Kruskal.cpp
        ListGraph.cpp
        Sorter.cpp
        GraphType.cpp
        GraphType.h
        GraphGenerator.cpp
        GraphGenerator.h
        IGraph.cpp
        IGraph.h
        Prim.h
        Prim.cpp
        TImer.cpp
        TImer.h
        FileHandler.cpp
        FileHandler.h
        Dijkstra.cpp
        Dijkstra.h
        BellmanFord.cpp
        BellmanFord.h
        MinHeap.cpp
        MinHeap.h
        ProblemType.h
)