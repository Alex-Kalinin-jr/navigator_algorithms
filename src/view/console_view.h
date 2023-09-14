#ifndef SRC_VIEW_CONSOLE_VIEW_H_
#define SRC_VIEW_CONSOLE_VIEW_H_

#include "../controller/controller.h"
#include "choice.h"

namespace s21 {



class ConsoleView {
 public:
  ConsoleView(Controller* c) : controller_(c){};
  void StartEventLoop();
  void DisplayMenu();
  int GetUserChoice();




  void HandleLoadGraph();
  void HandleBreadthFirstTraversal();
  void HandleDepthFirstTraversal();
  void HandleShortestPathSearch(int);
  void HandleTravelingSalesmanProblem(TsmResult &);

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