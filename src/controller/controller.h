#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../lib/s21_graph.h"
#include "../lib/s21_graph_algorithms.h"
#include "../view/choice.h"
#include "../view/console_view.h"

namespace s21 {

class ConsoleView;

class Controller {
 public:
  explicit Controller() : view_(nullptr) { graph_ = new Graph(); }
  Controller(const Controller &other) = delete;
  Controller &operator=(const Controller &other) = delete;
  ~Controller() { delete graph_; }

  void SetView(ConsoleView *);
  void ReceiveSignal(int);

 private:
  Graph *graph_;
  ConsoleView *view_;

  void LoadGraphFromFile();
  void ExportGraphToDot(const std::string &filename);
  void DepthFirstSearch();
  void BreadthFirstSearch();
  void GetShortestPathBetweenVertices();
  void GetShortestPathsBetweenAllVertices();
  void GetLeastSpanningTree();
  void SolveTravelingSalesmanProblem();
  void PrintMatrix() { graph_->PrintMatrix(); }
};

}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_