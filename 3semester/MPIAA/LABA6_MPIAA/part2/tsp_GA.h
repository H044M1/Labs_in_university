#include "graph.h"
#include <algorithm>
#include <vector>
#include <limits>
#include <numeric>
#include <queue>
#include <unordered_set>

double Random(double a, double b);
double length(const Graph &g, const std::vector<int> &path);
std::vector<int> RandomPath(const Graph &g);
std::vector<int> Transform(const std::vector<int> &path, const int &a, const int &b, const int &c, const int &d);
std::vector<int> TwoOptImprove(const Graph &graph, const std::vector<int> &path);
std::vector<int> CrossoverER(const std::vector<int> &parent1, const std::vector<int> &parent2);
std::vector<int> reversed(const std::vector<int> &path);
std::vector<int> start_with(const std::vector<int> &path, int vertex);
std::vector<int> min_dir(const std::vector<int> &path);
std::vector<int> aligned(const std::vector<int> &path, int start_vertex);
std::vector<int> TSP_GA(const Graph& g, int P, int N, int MaxIt, double Pm, bool informe);
