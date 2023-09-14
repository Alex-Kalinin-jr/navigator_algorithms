#include "console_view.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

namespace s21 {

void ConsoleView::DisplayMenu() {
  cout << "============" << endl;
  cout << "  M E N U   " << endl;
  cout << "============" << endl;
  cout << "1. Load the original graph from a file" << endl;
  cout << "2. Graph traversal in breadth" << endl;
  cout << "3. Graph traversal in depth" << endl;
  cout << "4. Search for the shortest path between two vertices" << endl;
  cout << "5. Search for the shortest paths between all pairs of vertices "
          "in the graph "
       << endl;
  cout << "6. Search for the minimal spanning tree in the graph" << endl;
  cout << "7. Solve the salesman problem" << endl;
  cout << "0. Quit" << endl << endl;
}

void ConsoleView::StartEventLoop() {
  int choice = NONE_C;
  while (choice != EXIT_C) {
    DisplayMenu();
    controller_->PrintMatrix();
    cin >> choice;
    switch ((Choice)choice) {
      case LOAD_GRAPH_C: {
        HandleLoadGraph();
        break;
      }
      case BREADTH_TRAVERSAL_C: {
        HandleBreadthFirstTraversal();
        break;
      }
      case DEAPTH_TRAVERSAL_C: {
        HandleDepthFirstTraversal();
        break;
      }
      case SEARCH_SHORTEST_PATH_C: {
        HandleShortestPathSearch();
        break;
      }
      case SEARCH_ALL_SHORTEST_PATHS_C: {
        HandleAllShortestPathsSearch();
        break;
      }
      case SEARCH_MINIMAL_SPANNING_TREE_C: {
        HandleMinimalSpanningTreeSearch();
        break;
      }
      case SALESMAN_PROBLEM_C: {
        HandleTravelingSalesmanProblem();
        break;
      }
      case EXIT_C: {
        cout << "Goodbye!" << endl;
        break;
      }
      default: {
        cout << "Invalid choice. Please try again." << endl;
        break;
      }
    }
  }
}

int ConsoleView::GetUserChoice() {
  int choice;
  cout << "Input a menu item digit: ";
  cin >> choice;
  return choice;
}

void ConsoleView::HandleLoadGraph() {
  std::string filename;
  cout << "Enter the filename: ";
  cin >> filename;
  controller_->LoadGraphFromFile(filename);
}

void ConsoleView::HandleBreadthFirstTraversal() {
  int start_vertex;
  cout << "Enter the start vertex: ";
  cin >> start_vertex;
  auto traversal = controller_->BreadthFirstSearch(start_vertex);
  DisplayTraversal(traversal);
}

void ConsoleView::HandleDepthFirstTraversal() {
  int start_vertex;
  cout << "Enter the start vertex: ";
  cin >> start_vertex;
  auto traversal = controller_->DepthFirstSearch(start_vertex);
  DisplayTraversal(traversal);
}

void ConsoleView::HandleShortestPathSearch() {
  int vertex1, vertex2;
  cout << "Enter the starting vertex: ";
  cin >> vertex1;
  cout << "Enter the ending vertex: ";
  cin >> vertex2;
  auto shortest_path =
      controller_->GetShortestPathBetweenVertices(vertex1, vertex2);
  DisplayShortestPath(shortest_path);
}

void ConsoleView::HandleAllShortestPathsSearch() {
  auto shortest_paths = controller_->GetShortestPathsBetweenAllVertices();
  DisplayShortestPaths(shortest_paths);
}

void ConsoleView::HandleMinimalSpanningTreeSearch() {
  auto least_spanning_tree = controller_->GetLeastSpanningTree();
  DisplayLeastSpanningTree(least_spanning_tree);
}

void ConsoleView::HandleTravelingSalesmanProblem() {
  try {
    auto tsm_result = controller_->SolveTravelingSalesmanProblem();
    cout << "Shortest tour distance: " << tsm_result.distance << endl;
    cout << "Tour vertices: ";
    for (int vertex : tsm_result.vertices) {
      cout << vertex << " ";
    }
    cout << endl;
  } catch (...) {
    std::cout<<"some errors occured. Maybe you forgot to load file?"<<std::endl;
  }
}

void ConsoleView::DisplayTraversal(const vector<int>& traversal) const {
  cout << "Traversal: ";
  for (const auto& vertex : traversal) {
    cout << vertex << " ";
  }
  cout << endl;
}

void ConsoleView::DisplayShortestPath(const int& shortest_path) const {
  if (shortest_path == 0) {
    cout << "No path found." << endl;
  } else {
    cout << "Shortest path: " << shortest_path << endl;
  }
}

void ConsoleView::DisplayShortestPaths(
    const vector<vector<int>>& shortest_paths) const {
  for (const auto& path : shortest_paths) {
    cout << "Path from vertex " << path[0] << ":" << endl;
    for (size_t i = 1; i < path.size(); ++i) {
      cout << path[i] << " ";
    }
    cout << endl;
  }
}

void ConsoleView::DisplayLeastSpanningTree(const vector<vector<int>>& tree) {
  cout << "The least spanning tree is:\n";
  for (int i = 0; i < static_cast<int>(tree.size()); ++i) {
    for (int j = i; j < static_cast<int>(tree.size()); ++j) {
      if (tree[i][j] > 0) {
        cout << i + 1 << " - " << j + 1 << " (" << tree[i][j] << ")\n";
      }
    }
  }
}

}  // namespace s21
