#include "controller.h"
#include "../view/console_view.h"

#include <string>
#include <iostream>

namespace s21 {

using std::cin;

void Controller::SetView(ConsoleView *view) {
  view_ = view;
}

void Controller::ReceiveSignal(int choice) {
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
  graph_->ExportGraphToDot(filename);
}

void Controller::DepthFirstSearch() {
  int start_vertex = view_-> GetUserChoice("Enter the start vertex:");
  auto traversal = GraphAlgorithms::DepthFirstSearch(*graph_, start_vertex);
  view_->DisplayTraversal(traversal);
}

void Controller::BreadthFirstSearch() {
  int start_vertex = view_-> GetUserChoice("Enter the start vertex:");
  auto traversal = GraphAlgorithms::BreadthFirstSearch(*graph_, start_vertex);
  view_->DisplayTraversal(traversal);
}

void Controller::GetShortestPathBetweenVertices() {
  int vertex1 = view_-> GetUserChoice("Enter the start vertex:");
  int vertex2 = view_-> GetUserChoice("Enter the end vertex:");
  auto shortest_path =
      GraphAlgorithms::GetShortestPathBetweenVertices(*graph_, vertex1,
                                                      vertex2);
  view_->DisplayShortestPath(shortest_path);
}

void Controller::GetShortestPathsBetweenAllVertices() {
  auto shortest_paths = 
      GraphAlgorithms::GetShortestPathsBetweenAllVertices(*graph_);
  view_->DisplayShortestPaths(shortest_paths);
}

void Controller::GetLeastSpanningTree() {
  auto least_spanning_tree = GraphAlgorithms::GetLeastSpanningTree(*graph_);
  view_->DisplayLeastSpanningTree(least_spanning_tree);
}

void Controller::SolveTravelingSalesmanProblem() {
  if (graph_->Size() == 0) {
    view_->ShowError("Maybe you forgot to load file?");
  }
  try {
    auto tsm_result = 
        GraphAlgorithms::SolveTravelingSalesmanProblem(*graph_);
    view_->HandleTravelingSalesmanProblem(tsm_result);
  } catch(...) {
    view_->ShowError("some errors occured.");
  }
}

}  // namespace s21
