#ifndef SRC_LIB_S21_GRAPH_ALGORITHMS_H_
#define SRC_LIB_S21_GRAPH_ALGORITHMS_H_

#include <limits>
#include <string>
#include <vector>

#include "s21_graph.h"
#include "s21_queue.h"
#include "s21_stack.h"

namespace s21 {

using std::vector;

const int kNumAnts = 100;
const int kNumIterations = 15000;
const double kAlpha = 1.0;
const double kBeta = 2.0;
const double kRHO = 0.5;
const double kQ = 100.0;
const double kInitialPheromone = 0.1;
const int kInf = std::numeric_limits<int>::max();

struct TsmResult {
  std::vector<int> vertices;
  double distance;
};

struct Ant {
  vector<int> path;
  // vector<bool> visited;
  double path_length;
};

class GraphAlgorithms {
public:
  // Part1
  static vector<int> DepthFirstSearch(const Graph &graph, const int start);
  static vector<int> BreadthFirstSearch(const Graph &graph, const int start);

  // Part2
  static int GetShortestPathBetweenVertices(const Graph &graph,
                                            const int vertex1,
                                            const int vertex2);
  static vector<vector<int>>
  GetShortestPathsBetweenAllVertices(const Graph &graph);

  // // Part3
  static vector<vector<int>> GetLeastSpanningTree(const Graph &graph);

  // Part4
  static TsmResult SolveTravelingSalesmanProblem(const Graph &graph);
  //
  static double Distance(int i, int j, const Graph &graph);
  static double Eta(int i, int j, const Graph &graph);
  static vector<vector<double>> InitializePheromone(int n);
  static void UpdatePheromone(vector<vector<double>> &pheromone,
                              const vector<TsmResult> &ants);

  static int SelectNext(int current, const vector<bool> &visited,
                        const vector<vector<double>> &pheromone,
                        const Graph &graph);
  static TsmResult BuildTour(int start, vector<bool> &visited,
                             const vector<vector<double>> &pheromone,
                             const Graph &graph);
  static double Random();
};

} // namespace s21

#endif // SRC_LIB_S21_GRAPH_ALGORITHMS_H_