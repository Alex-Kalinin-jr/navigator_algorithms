#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../lib/s21_graph.h"
#include "../lib/s21_graph_algorithms.h"
// #include "../model/navigator.h"

namespace s21 {

class Controller {
 public:
  explicit Controller() { graph_ = new Graph(); }

  Controller(const Controller &other) = delete;
  Controller &operator=(const Controller &other) = delete;

  ~Controller() { delete graph_; }

  void LoadGraphFromFile(const std::string &filename);
  void ExportGraphToDot(const std::string &filename);
  vector<int> DepthFirstSearch(int start_vertex);
  vector<int> BreadthFirstSearch(int start_vertex);
  int GetShortestPathBetweenVertices(int vertex1, int vertex2);
  vector<vector<int>> GetShortestPathsBetweenAllVertices();
  vector<vector<int>> GetLeastSpanningTree();
  TsmResult SolveTravelingSalesmanProblem();
  void PrintMatrix() { graph_->PrintMatrix(); }

 private:
  Graph *graph_;
};

}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_