#include "controller.h"

#include <string>
#include <iostream>

#include "../view/console_view.h"


namespace s21 {

using std::cin;

void Controller::SetView(ConsoleView *view) {
  view_ = view;
}

void Controller::ReceiveSignal(int choice) {
  static_assert(CHOICE_END == 8, "not all the cases:check choice.h");
  switch ((Choice)choice) {
        case LOAD_GRAPH_C: {
          LoadGraphFromFile();
          view_-> GetString("press any key to continue");
          break;
        }
        case BREADTH_TRAVERSAL_C: {
          DepthFirstSearch();
          view_-> GetString("press any key to continue");
          break;
        }
        case DEAPTH_TRAVERSAL_C: {
          BreadthFirstSearch();
          view_-> GetString("press any key to continue");
          break;
        }
        case SEARCH_SHORTEST_PATH_C: {
          GetShortestPathBetweenVertices();
          view_-> GetString("press any key to continue");
          break;
        }
        case SEARCH_ALL_SHORTEST_PATHS_C: {
          GetShortestPathsBetweenAllVertices();
          view_-> GetString("press any key to continue");
          break;
        }
        case SEARCH_MINIMAL_SPANNING_TREE_C: {
          GetLeastSpanningTree();
          view_-> GetString("press any key to continue");
          break;
        }
        case SALESMAN_PROBLEM_C: {
          SolveTravelingSalesmanProblem();
          view_-> GetString("press any key to continue");
          break;
        }
        default: {}
  }
}

void Controller::LoadGraphFromFile() {
  std::string filename = view_->GetString("Enter the filename:");
  try {
    graph_->LoadGraphFromFile(filename);
    graph_->PrintMatrix();
  } catch(...) {
    view_->ShowError("File does'n loaded");
  }
}

void Controller::ExportGraphToDot() {
  std::string filename = view_->GetString("Enter the filename:");
  try {
    graph_->ExportGraphToDot(filename);
  } catch (...) {
    view_->ShowError("Error. Is graph loaded?");
  }
}

void Controller::DepthFirstSearch() {
  int start_vertex = view_-> GetUserChoice("Enter the start vertex:");
  try {
    auto traversal = GraphAlgorithms::DepthFirstSearch(*graph_, start_vertex - 1);
    view_->DisplayTraversal(traversal);
  } catch (...) {
    view_->ShowError("Error. Is graph loaded? Is vertex correct?");
  }
}

void Controller::BreadthFirstSearch() {
  int start_vertex = view_-> GetUserChoice("Enter the start vertex:");
  try {
    auto traversal = GraphAlgorithms::BreadthFirstSearch(*graph_, start_vertex - 1);
    view_->DisplayTraversal(traversal);
  } catch (...) {
    view_->ShowError("Error. Is graph loaded? Is vertex correct?");
  }
}

void Controller::GetShortestPathBetweenVertices() {
  int vertex1 = view_-> GetUserChoice("Enter the start vertex:");
  int vertex2 = view_-> GetUserChoice("Enter the end vertex:");
  try {
    auto shortest_path =
        GraphAlgorithms::GetShortestPathBetweenVertices(*graph_, vertex1,
                                                        vertex2);
    view_->DisplayShortestPath(shortest_path);
  } catch (...) {
    view_->ShowError("Error. Is graph loaded? Is vertex correct?");
  }
}

void Controller::GetShortestPathsBetweenAllVertices() {
  try {
    auto shortest_paths = 
        GraphAlgorithms::GetShortestPathsBetweenAllVertices(*graph_);
    view_->DisplayShortestPaths(shortest_paths);
  } catch (...) {
    view_->ShowError("Error. Is graph loaded? Is vertex correct?");
  }
}

void Controller::GetLeastSpanningTree() {
  try {
    auto least_spanning_tree = GraphAlgorithms::GetLeastSpanningTree(*graph_);
    view_->DisplayLeastSpanningTree(least_spanning_tree);
  } catch (...) {
    view_->ShowError("Error. Is graph loaded? Is vertex correct?");
  }
}

void Controller::SolveTravelingSalesmanProblem() {
  try {
    auto tsm_result = 
        GraphAlgorithms::SolveTravelingSalesmanProblem(*graph_);
    view_->HandleTravelingSalesmanProblem(tsm_result);
  } catch(...) {
    view_->ShowError("Error. Is graph loaded? Is vertex correct?");
  }
}

}  // namespace s21
