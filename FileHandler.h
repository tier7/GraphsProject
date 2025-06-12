#include <fstream>

#include "MatrixGraph.h"
#include "ListGraph.h"
#include <iostream>


// klasa wczytujaca dane z pliku
class FileHandler {
public:
    //wczytywanie grafu w reprezentacji macierzowej z pliku
    static MatrixGraph* loadMatrixGraphFromFile(const std::string &filename, GraphType t = UNDIRECTED) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Cannot open file: " << filename << std::endl;
            return nullptr;
        }
        int v, e;
        file >> e >> v;
        if (!file || v <= 0 || e < 0) {
            std::cerr << "Invalid edges or nodes in " << filename << std::endl;
            return nullptr;
        }
        MatrixGraph* g = new MatrixGraph(v, e, t);

        for (int i = 0; i < e; i++) {
            int u, v2, w;
            file >> u >> v2 >> w;
            if (!file || u < 0 || v2 < 0 || w <= 0) {
                std::cerr << "Error reading edge " << i << std::endl;
                delete g;
                return nullptr;
            }
            g->addEdge(u, v2, w);
        }
        return g;
    }
    // wczytywanie grafu w reprezentacji listowej z pliku
    static ListGraph* loadListGraphFromFile(const std::string &filename, GraphType t = UNDIRECTED) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Cannot open file: " << filename << std::endl;
            return nullptr;
        }
        int v, e;
        file >> e>> v;
        if (!file || v <= 0 || e < 0) {
            std::cerr << "Invalid edges or nodes in " << filename << std::endl;
            return nullptr;
        }
        ListGraph* g = new ListGraph(v, t);

        for (int i = 0; i < e; i++) {
            int u, v2, w;
            file >> u >> v2 >> w;
            if (!file || u < 0 || v2 < 0 || w <= 0) {
                std::cerr << "Error reading edge " << i << std::endl;
                delete g;
                return nullptr;
            }
            g->addEdge(u, v2, w);
        }
        return g;
    }
};
