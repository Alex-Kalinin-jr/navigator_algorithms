#include "controller.h"

namespace s21 {

void Controller::LoadGraphFromFile(const std::string &filename) {
  graph_->LoadGraphFromFile(filename);
}

void Controller::ExportGraphToDot(const std::string &filename) {
  graph_->ExportGraphToDot(filename);
}

vector<int> Controller::DepthFirstSearch(int start_vertex) {
  return GraphAlgorithms::DepthFirstSearch(*graph_, start_vertex);
}

vector<int> Controller::BreadthFirstSearch(int start_vertex) {
  return GraphAlgorithms::BreadthFirstSearch(*graph_, start_vertex);
}

int Controller::GetShortestPathBetweenVertices(int vertex1, int vertex2) {
  return GraphAlgorithms::GetShortestPathBetweenVertices(*graph_, vertex1,
                                                         vertex2);
}

vector<vector<int>> Controller::GetShortestPathsBetweenAllVertices() {
  return GraphAlgorithms::GetShortestPathsBetweenAllVertices(*graph_);
}

vector<vector<int>> Controller::GetLeastSpanningTree() {
  return GraphAlgorithms::GetLeastSpanningTree(*graph_);
}

TsmResult Controller::SolveTravelingSalesmanProblem() {
  if (graph_->Size() == 0) {
    throw "empty graph";
  }
  return GraphAlgorithms::SolveTravelingSalesmanProblem(*graph_);
}

}  // namespace s21
