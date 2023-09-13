#ifndef SRC_VIEW_CONSOLE_VIEW_H_
#define SRC_VIEW_CONSOLE_VIEW_H_

#include "../controller/controller.h"

namespace s21 {

enum Choice {
  NONE_C = -1,
  EXIT_C = 0,
  LOAD_GRAPH_C = 1,
  BREADTH_TRAVERSAL_C = 2,
  DEAPTH_TRAVERSAL_C = 3,
  SEARCH_SHORTEST_PATH_C = 4,
  SEARCH_ALL_SHORTEST_PATHS_C = 5,
  SEARCH_MINIMAL_SPANNING_TREE_C = 6,
  SALESMAN_PROBLEM_C = 7
};

class ConsoleView {
 public:
  ConsoleView(Controller* c) : controller_(c){};
  void DisplayMenu();
  void StartEventLoop();
  int GetUserChoice();

  void HandleLoadGraph();
  void HandleBreadthFirstTraversal();
  void HandleDepthFirstTraversal();
  void HandleShortestPathSearch();
  void HandleAllShortestPathsSearch();
  void HandleMinimalSpanningTreeSearch();
  void HandleTravelingSalesmanProblem();

  void DisplayTraversal(const std::vector<int>& traversal) const;
  void DisplayShortestPath(const int& shortest_path) const;
  void DisplayShortestPaths(
      const std::vector<std::vector<int>>& shortest_paths) const;
  void DisplayLeastSpanningTree(const std::vector<std::vector<int>>& tree);

 private:
  Controller* controller_;
};

}  // namespace s21

#endif  // SRC_VIEW_CONSOLE_VIEW_H_