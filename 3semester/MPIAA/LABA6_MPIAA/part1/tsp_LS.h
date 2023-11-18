#include "graph.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

double length(const Graph &g, const std::vector<int> &path);
std::vector<int> TSP_LS(const Graph& graph);
std::vector<int> Transform(const std::vector<int>& path, int i, int j);
double calculate_path_length(const std::vector<int>& path, const Graph& graph);