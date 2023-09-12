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
  void ExportGraphToDot(std::string filename) const;
  void PrintMatrix() const;

  int GetEdgeWeight(int i, int j) const;
  int Size() const;
  vector<int> Neighbors(int vertex) const;
  vector<int> NeighborsFromEnd(int vertex) const;

 private:
  bool IsDirected() const;
  void ExportEdgeWeight(std::ofstream &file, int i, int j) const;
  void Export(std::ofstream &file, const bool direction) const;
  void CheckCorrectness(vector<vector<int>> &vctr, int &size) const;
  void CheckLineCorrectness(std::string &) const;

  vector<vector<int>> adjacency_matrix_;
};

}  // namespace s21

#endif  // SRC_LIB_S21_GRAPH_H_