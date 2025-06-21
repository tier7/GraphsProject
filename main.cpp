#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "GraphType.h"
#include "GraphGenerator.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include "Timer.h"
#include "FileHandler.h"
#include <string.h>
#include "ProblemType.h"

void runTests() {
    int sizes[7] = {400,500,600,700,800,900,1000};
    float densities[3] = {0.25f, 0.5f, 0.99f};
    int nSizes = 7, nDensities = 3;
    int reps = 50;
    int minW = 1, maxW = 100;
    const int INF = INT_MAX / 4;
    std::ofstream csv("wyniki.csv");
    csv << "powtorzenie,algorytm,reprezentacja,rozmiar,gestosc,czas(ms),koszt\n";
    std::ofstream avgcsv("avgwyniki.csv");
    avgcsv << "algorytm,reprezentacja,rozmiar,gestosc,sredni_czas(ms)\n";

    for (int i = 0; i < nSizes; i++) {
        int size = sizes[i];
        for (int j = 0; j < nDensities; j++) {
            float dens = densities[j];
            double primMatrixSum = 0, primListSum = 0, kruskalMatrixSum = 0, kruskalListSum = 0;
            double dijkstraMatrixSum = 0, dijkstraListSum = 0, bellmanMatrixSum = 0, bellmanListSum = 0;
            for (int rep = 0; rep < reps; rep++) {
                int maxE_MST = edgesCalculate(size, dens, UNDIRECTED);
                int maxE_SP = edgesCalculate(size, dens, DIRECTED);
                MatrixGraph matrixMST(size, maxE_MST, UNDIRECTED);
                ListGraph listMST(size, UNDIRECTED);
                generateGraph(matrixMST, dens, minW, maxW, UNDIRECTED);
                // tworzenie kopii grafu w formie listowej
                int edgCountMST;
                Edge* edgesMST = matrixMST.getEdges(edgCountMST);
                for (int v = 0; v < edgCountMST; v++)
                    listMST.addEdge(edgesMST[v].from, edgesMST[v].destination, edgesMST[v].weight);
                delete[] edgesMST;

                Timer t1;
                t1.start();
                int cost1 = Prim(matrixMST);
                double time1 = t1.end();
                csv << rep << ",Prim,Matrix," << size << "," << dens << "," << time1 << "," << cost1 << "\n";
                primMatrixSum += time1;

                Timer t2;
                t2.start();
                int cost2 = Prim(listMST);
                double time2 = t2.end();
                csv << rep << ",Prim,List," << size << "," << dens << "," << time2 << "," << cost2 << "\n";
                primListSum += time2;

                Timer t3;
                t3.start();
                int cost3 = Kruskal(matrixMST);
                double time3 = t3.end();
                csv << rep << ",Kruskal,Matrix," << size << "," << dens << "," << time3 << "," << cost3 << "\n";
                kruskalMatrixSum += time3;

                Timer t4;
                t4.start();
                int cost4 = Kruskal(listMST);
                double time4 = t4.end();
                csv << rep << ",Kruskal,List," << size << "," << dens << "," << time4 << "," << cost4 << "\n";
                kruskalListSum += time4;

                MatrixGraph matrixSP(size, maxE_SP, DIRECTED);
                ListGraph listSP(size, DIRECTED);
                generateGraph(matrixSP, dens, minW, maxW, DIRECTED);
                // tworzenie kopii grafu w formie listowej
                int edgCountSP;
                Edge* edgesSP = matrixSP.getEdges(edgCountSP);
                for (int v = 0; v < edgCountSP; v++)
                    listSP.addEdge(edgesSP[v].from, edgesSP[v].destination, edgesSP[v].weight);
                delete[] edgesSP;

                int start = rand() % size;
                Timer t5;
                t5.start();
                int* dist5 = Dijkstra(matrixSP, start);
                double time5 = t5.end();
                long long cost5 = 0;
                for (int k = 0; k < size; ++k) {
                    if (dist5[k] != INF) {
                        cost5 += dist5[k];
                    }
                }
                csv << rep << ",Dijkstra,Matrix," << size << "," << dens << "," << time5 << "," << cost5 << "\n";
                delete[] dist5;
                dijkstraMatrixSum += time5;

                Timer t6;
                t6.start();
                int* dist6 = Dijkstra(listSP, start);
                double time6 = t6.end();
                long long cost6 = 0;
                for (int k = 0; k < size; ++k) {
                    if (dist6[k] != INF) {
                        cost6 += dist6[k];
                    }
                }
                csv << rep << ",Dijkstra,List," << size << "," << dens << "," << time6 << "," << cost6 << "\n";
                delete[] dist6;
                dijkstraListSum += time6;

                Timer t7;
                t7.start();
                int* dist7 = BellmanFord(matrixSP, start);
                double time7 = t7.end();
                long long cost7 = 0;
                for (int k = 0; k < size; ++k) {
                    if (dist7[k] != INF) {
                        cost7 += dist7[k];
                    }
                }
                csv << rep << ",BellmanFord,Matrix," << size << "," << dens << "," << time7 << "," << cost7 << "\n";
                delete[] dist7;
                bellmanMatrixSum += time7;

                Timer t8;
                t8.start();
                int* dist8 = BellmanFord(listSP, start);
                double time8 = t8.end();
                long long cost8 = 0;
                for (int k = 0; k < size; ++k) {
                    if (dist8[k] != INF) {
                        cost8 += dist8[k];
                    }
                }
                csv << rep << ",BellmanFord,List," << size << "," << dens << "," << time8 << "," << cost8 << "\n";
                delete[] dist8;
                bellmanListSum += time8;
            }
            std::cout << "Zakonczono wykonywanie testu dla rozmiaru:" << size << " i gestosci=" << dens << std::endl;
            avgcsv << "Prim,Matrix," << size << "," << dens << "," << (primMatrixSum / reps) << "\n";
            avgcsv << "Prim,List," << size << "," << dens << "," << (primListSum / reps) << "\n";
            avgcsv << "Kruskal,Matrix," << size << "," << dens << "," << (kruskalMatrixSum / reps) << "\n";
            avgcsv << "Kruskal,List," << size << "," << dens << "," << (kruskalListSum / reps) << "\n";
            avgcsv << "Dijkstra,Matrix," << size << "," << dens << "," << (dijkstraMatrixSum / reps) << "\n";
            avgcsv << "Dijkstra,List," << size << "," << dens << "," << (dijkstraListSum / reps) << "\n";
            avgcsv << "BellmanFord,Matrix," << size << "," << dens << "," << (bellmanMatrixSum / reps) << "\n";
            avgcsv << "BellmanFord,List," << size << "," << dens << "," << (bellmanListSum / reps) << "\n";
        }
    }
    csv.close();
    std::cout << "Zakonczono testy - wyniki w pliku wyniki.csv\n";
    std::cout << "Usrednione wyniki w pliku avgwyniki.csv\n";
}
void fileMode(const std::string& configFile) {
    ProblemType gProblem = MST;
    std::ifstream fin(configFile);
    if (!fin.is_open()) {
        std::cerr << "Cannot open file: " << configFile << std::endl;
        return;
    }

    IGraph* graph = nullptr;
    std::string line;
    while (getline(fin, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "problem") {
            std::string p; iss >> p;
            if (p == "MST") gProblem = MST;
            else if (p == "SP") gProblem = SP;
            else std::cerr << "unknown problem\n";
            continue;
        }

        if (cmd == "random") {
            int V, minW, maxW;
            float dens;
            std::string repr;
            iss >> V >> dens >> minW >> maxW >> repr;
            delete graph;
            GraphType gType = (gProblem == MST ? UNDIRECTED : DIRECTED);
            if (repr == "matrix") {
                int maxE = edgesCalculate(V, dens, gType);
                graph = new MatrixGraph(V, maxE, gType);
                generateGraph(*graph, dens, minW, maxW, gType);
            } else if (repr == "list") {
                graph = new ListGraph(V, gType);
                generateGraph(*graph, dens, minW, maxW, gType);
            }
            std::cout << "generated graph (" << V << " nodes and " << dens << " density)\n";
        }

        else if (cmd == "file") {
            std::string fname, repr;
            iss >> fname >> repr;
            delete graph;
            GraphType gType = (gProblem == MST ? UNDIRECTED : DIRECTED);
            if (repr == "matrix") {
                graph = FileHandler::loadMatrixGraphFromFile(fname, gType);
            }
            else if (repr == "list") {
                graph = FileHandler::loadListGraphFromFile(fname, gType);
            }
            if (graph) std::cout << "loaded graph from file " << fname << "\n";
            else std::cerr << "error with loading from file\n";
        }

        else if (cmd == "show") {
            if (graph) graph->print();
            else std::cerr << "graph doesn't exist\n";
        }

        else if (cmd == "prim") {
            if (!graph) { std::cerr << "graph doesn't exist\n"; continue; }
            if (graph->getGraphType() == DIRECTED) { std::cerr << "wrong graph type\n"; continue; }
            std::cout << "Prim: " << Prim(*graph) << "\n";
        }

        else if (cmd == "kruskal") {
            if (!graph) { std::cerr << "graph doesn't exist\n"; continue; }
            if (graph->getGraphType() == DIRECTED) { std::cerr << "wrong graph type\n"; continue; }
            std::cout << "Kruskal: " << Kruskal(*graph) << "\n";
        }

        else if (cmd == "dijkstra") {
            int start; iss >> start;
            if (graph) {
                int* dist = Dijkstra(*graph, start);
                int n = graph->getVerticesCount();
                for (int i = 0; i < n; ++i) std::cout << "Koszt do " << i << ": " << dist[i] << "\n";
                delete[] dist;
            } else std::cerr << "graph doesn't exist\n";
        }

        else if (cmd == "bellman") {
            int start; iss >> start;
            if (!graph) { std::cerr << "graph doesn't exist\n"; continue; }
            if (graph->getGraphType() == UNDIRECTED) { std::cerr << "wrong graph type\n"; continue; }
            int* dist = BellmanFord(*graph, start);
            int n = graph->getVerticesCount();
            for (int i = 0; i < n; ++i) std::cout << "Koszt do " << i << ": " << dist[i] << "\n";
            delete[] dist;
        }
    }
    delete graph;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    while (true) {
        std::cout << "1. Test algorytmow\n";
        std::cout << "2. Testowanie z pliku\n";
        std::cout << "0. Exit\n";
        int opt; std::cin >> opt;
        if (opt == 0) break;
        else if (opt == 1) runTests();
        else if (opt == 2) {
            std::string fname;
            std::cout << "nazwa pliku konfiguracyjnego: ";
            std::cin >> fname;
            fileMode(fname);
        }
    }
    return 0;
}
