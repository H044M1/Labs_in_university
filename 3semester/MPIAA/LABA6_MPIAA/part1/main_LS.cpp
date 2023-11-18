#include "graph.h"
#include <tuple>
#include <random>
#include <iostream>
#include "tsp.h"
#include "tsp_LS.h"
#include <chrono>
#include <vector> 
#include <unordered_set>
#include <unordered_map>

using namespace std::chrono;
using namespace std;

Graph random_graph(int size) {
    Graph graph;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution_distance(10, 100);

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            graph.add_edge(i, j, distribution_distance(generator) / 10.0);
        }
    }
    return graph;
}

int main(int argc, char* argv[]) {
    int multi = 2;
    int size_stop = 1000;
    int N = 64;
    while (N <= size_stop) {
    Graph graph = random_graph(N);
    cout << "Start for graph size : " << N << endl;
    double time_stop = 10;
    double time1 = 0;
    auto t1 = std::chrono::high_resolution_clock::now(); // Record time before executing the algorithm
    std::vector<int> result = TSP_LS(graph);
    auto t2 = std::chrono::high_resolution_clock::now(); // Record time after executing the algorithm
    time1 = std::chrono::duration<double>(t2 - t1).count(); // Calculate the time difference
    std::cout << "TSP_GA: " << "N = " << N << ", " << "time = " << time1 << " seconds " << std::endl;
    std::cout << "Path:" << std::endl;
    for (auto it : result) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    std::cout << "Path lenght: " << length(graph, result) << std::endl;
    N *= multi;
    }
    return 0;
}