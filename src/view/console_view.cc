#include "console_view.h"

#include <iostream>
#include <cstdlib>
#include <iostream>

#include "choice.h"

namespace s21 {

void ConsoleView::StartEventLoop() const {
  int choice = EXIT_C - 1;
  while (true) {
    DisplayMenu();
    while (choice < EXIT_C || choice >= CHOICE_END) {
      choice = GetUserChoice("Choose mod");
    }
    if (choice == EXIT_C) {
      break;
    }
    controller_->ReceiveSignal(choice);
    choice = EXIT_C - 1;
  }
}


void ConsoleView::DisplayMenu() const {
  system("clear");
  std::cout << "============" << std::endl;
  std::cout << "  M E N U   " << std::endl;
  std::cout << "============" << std::endl;
  std::cout << "1. Load the original graph from a file" << std::endl;
  std::cout << "2. Graph traversal in breadth" << std::endl;
  std::cout << "3. Graph traversal in depth" << std::endl;
  std::cout << "4. Search for the shortest path between two vertices" << std::endl;
  std::cout << "5. Search for the shortest paths between all pairs of vertices"
          "in the graph " << std::endl;
  std::cout << "6. Search for the minimal spanning tree in the graph" << std::endl;
  std::cout << "7. Solve the salesman problem" << std::endl;
  std::cout << "0. Quit" << std::endl << std::endl;
}


int ConsoleView::GetUserChoice(std::string message) const {
  std::cout << message <<std::endl;
  int choice = EXIT_C - 1;
  std::string buff_str;
  std::getline(std::cin, buff_str);
  while (sscanf(buff_str.c_str(), "%d", &choice) != 1) {
    std::getline(std::cin, buff_str);
  }
  return choice;
}


std::string ConsoleView::GetString(std::string message) const {
  std::cin.clear();
  std::cout << message << std::endl;
  std::string filename;
  std::cin >> filename;
  return filename;
}

void ConsoleView::ShowError(std::string error) {
  std::cout << error << std::endl;
}

void ConsoleView::HandleTravelingSalesmanProblem(TsmResult &tsm_result) const {
    if (std::numeric_limits<double>::max() == tsm_result.distance) {
      std::cout << "path not found";
    } else {
      std::cout << "Shortest tour distance: " << tsm_result.distance << std::endl;
      std::cout << "Tour vertices: ";
      for (int vertex : tsm_result.vertices) {
        std::cout << vertex << " ";
      }
    }
    std::cout << std::endl;
}

void ConsoleView::DisplayTraversal(const vector<int>& traversal) const {
  std::cout << "Traversal: ";
  for (const auto& vertex : traversal) {
    std::cout << vertex << " ";
  }
  std::cout << std::endl;
}

void ConsoleView::DisplayShortestPath(const int& shortest_path) const {
  if (shortest_path == 0) {
    std::cout << "No path found." << std::endl;
  } else {
    std::cout << "Shortest path: " << shortest_path << std::endl;
  }
}

void ConsoleView::DisplayShortestPaths(
    const vector<vector<int>>& shortest_paths) const {
  for (const auto& path : shortest_paths) {
    std::cout << "Path from vertex " << path[0] << ":" << std::endl;
    for (size_t i = 1; i < path.size(); ++i) {
      std::cout << path[i] << " ";
    }
    std::cout << std::endl;
  }
}

void ConsoleView::DisplayLeastSpanningTree(const Matrix& tree) const {
  std::cout << "The least spanning tree is:\n";
  for (int i = 0; i < static_cast<int>(tree.size()); ++i) {
    for (int j = i; j < static_cast<int>(tree.size()); ++j) {
      if (tree[i][j] > 0) {
        std::cout << i + 1 << " - " << j + 1 << " (" 
                  << tree[i][j] << ")" << std::endl;
      }
    }
  }
}

}  // namespace s21
