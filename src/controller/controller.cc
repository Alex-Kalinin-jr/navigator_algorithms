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
          break;
        }
        case BREADTH_TRAVERSAL_C: {
          DepthFirstSearch();
          break;
        }
        case DEAPTH_TRAVERSAL_C: {
          BreadthFirstSearch();
          break;
        }
        case SEARCH_SHORTEST_PATH_C: {
          GetShortestPathBetweenVertices();
          break;
        }
        case SEARCH_ALL_SHORTEST_PATHS_C: {
          GetShortestPathsBetweenAllVertices();
          break;
        }
        case SEARCH_MINIMAL_SPANNING_TREE_C: {
          GetLeastSpanningTree();
          break;
        }
        case SALESMAN_PROBLEM_C: {
          SolveTravelingSalesmanProblem();
          break;
        }
        default: {}
  }
}

void Controller::LoadGraphFromFile() {
  std::string filename;
  view_-> HandleLoadGraph();
  std::getline(std::cin, filename);
  graph_->LoadGraphFromFile(filename);
}


//F*******************************************to be rewritten
void Controller::ExportGraphToDot(const std::string &filename) {
  graph_->ExportGraphToDot(filename);
}
//F*******************************************to be rewritten

void Controller::DepthFirstSearch() {
  view_->HandleBreadthFirstTraversal();
  int start_vertex;
  cin >> start_vertex;
  auto traversal = GraphAlgorithms::DepthFirstSearch(*graph_, start_vertex);
  view_->DisplayTraversal(traversal);
}

void Controller::BreadthFirstSearch() {
  view_->HandleDepthFirstTraversal();
  int start_vertex;
  cin >> start_vertex;
  auto traversal = GraphAlgorithms::BreadthFirstSearch(*graph_, start_vertex);
  view_->DisplayTraversal(traversal);
}

void Controller::GetShortestPathBetweenVertices() {
  int vertex1, vertex2;
  view_->HandleShortestPathSearch(0);
  cin >> vertex1;
  view_->HandleShortestPathSearch(1);
  cin >> vertex2;
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
    throw "empty graph";
  }

  auto tsm_result = 
      GraphAlgorithms::SolveTravelingSalesmanProblem(*graph_);
  view_->HandleTravelingSalesmanProblem(tsm_result);
}

}  // namespace s21
