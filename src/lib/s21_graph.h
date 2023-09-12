#ifndef SRC_LIB_S21_GRAPH_H_
#define SRC_LIB_S21_GRAPH_H_

#include <iostream>
#include <string>
#include <vector>

namespace s21 {

using std::vector;

class Graph {
 public:
  explicit Graph(){};

  void LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(std::string filename);
  void PrintMatrix() const {
    for (int i = 0; i < Size(); ++i) {
      for (int j = 0; j < Size(i); ++j) {
        std::cout << adjacency_matrix_[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  int GetEdgeWeight(int i, int j) const;
  int Size() const;
  vector<int> Neighbors(int vertex) const;
  vector<int> NeighborsFromEnd(int vertex) const;

 private:
  bool IsDirected();
  int Size(int i) const;
  void ExportDirected(std::ofstream &file);
  void ExportUndirected(std::ofstream &file);
  void ExportEdgeWeight(std::ofstream &file, int i, int j);

  void CheckCorrectness(vector<vector<int>> &vctr, int &size) const;
  void CheckLineCorrectness(std::string &) const;

  vector<vector<int>> adjacency_matrix_ = {{0, 5, 4}, {5, 0, 2}, {4, 2, 0}};
};

}  // namespace s21

#endif  // SRC_LIB_S21_GRAPH_H_