#include "console_view.h"
#include "choice.h"

#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

namespace s21 {

void ConsoleView::StartEventLoop() const {
  int choice = NONE_C;
  while (true) {
    DisplayMenu();
    cin >> choice;
    if (choice == EXIT_C) {
      break;
    }
    if (choice >= CHOICE_END && choice < EXIT_C) {
      cout << "Invalid choice. Please try again." << endl;
      continue;
    }
    std::system("clear");
    controller_->ReceiveSignal(choice);
  }
}


void ConsoleView::DisplayMenu() const {
  std::system("clear");
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


int ConsoleView::GetUserChoice(std::string message) const {
  std::cout << message <<std::endl;
  int choice;
  cin >> choice;
  return choice;
}


std::string ConsoleView::GetString(std::string message) const {
  std::cout << message <<std::endl;
  std::string filename;
  std::getline(std::cin, filename);
  return filename;
}

void ConsoleView::ShowError(std::string error) {
  cout << error << endl;
}

void ConsoleView::HandleTravelingSalesmanProblem(TsmResult &tsm_result) const {
    cout << "Shortest tour distance: " << tsm_result.distance << endl;
    cout << "Tour vertices: ";
    for (int vertex : tsm_result.vertices) {
      cout << vertex << " ";
    }
    cout << endl;
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

void ConsoleView::DisplayLeastSpanningTree(const Matrix& tree) const {
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
