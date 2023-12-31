#ifndef NAVIGATOR_SRC_LIB_S21_GRAPH_H_
#define NAVIGATOR_SRC_LIB_S21_GRAPH_H_

#include <iostream>
#include <string>
#include <vector>

namespace s21 {

using std::vector;

class Graph {
public:
  Graph() = default;

  void LoadGraphFromFile(std::string filename);

  void ExportGraphToDot(std::string filename) const;
  void PrintMatrix() const;
  int Size() const;
  int GetEdgeWeight(const int &i, const int &j) const;
  vector<int> Neighbors(const int &vertex) const;
  vector<int> NeighborsFromEnd(const int &vertex) const;

private:
  bool IsDirected() const;
  void ExportEdgeWeight(std::ofstream &file, const int &i, const int &j) const;
  void Export(std::ofstream &file, const bool direction) const;
  void CheckCorrectness(vector<vector<int>> &vctr, const int &size) const;
  void CheckLineCorrectness(const std::string &) const;

  vector<vector<int>> adjacency_matrix_;
};

} // namespace s21

#endif // NAVIGATOR_SRC_LIB_S21_GRAPH_H_