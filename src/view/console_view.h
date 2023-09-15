#ifndef NAVIGATOR_SRC_VIEW_CONSOLE_VIEW_H_
#define NAVIGATOR_SRC_VIEW_CONSOLE_VIEW_H_

#include "../controller/controller.h"
#include "choice.h"

namespace s21 {

class Controller;

class ConsoleView {
 public:
  ConsoleView(Controller* c) : controller_(c){};
  // interactions with user
  void StartEventLoop() const;
  void DisplayMenu() const;
  int GetUserChoice(std::string) const;
  std::string GetString(std::string) const;
  void ShowError(std::string);

  // actions after interaction
  void HandleTravelingSalesmanProblem(TsmResult &) const;
  void DisplayTraversal(const std::vector<int>& traversal) const;
  void DisplayShortestPath(const int& shortest_path) const;
  void DisplayShortestPaths(const Matrix& shortest_paths) const;
  void DisplayLeastSpanningTree(const Matrix& tree) const;

 private:
  Controller* controller_;
};

}  // namespace s21

#endif  // NAVIGATOR_SRC_VIEW_CONSOLE_VIEW_H_