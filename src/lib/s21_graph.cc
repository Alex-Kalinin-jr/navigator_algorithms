#include "s21_graph.h"

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

int Graph::GetEdgeWeight(const int &i, const int &j) const {
  return adjacency_matrix_[i][j];
}

int Graph::Size() const { return static_cast<int>(adjacency_matrix_.size()); }

bool Graph::IsDirected() const {
  for (int i = 0; i < Size(); ++i) {
    for (int j = i + 1; j < Size(); ++j) {
      if (adjacency_matrix_[i][j] != adjacency_matrix_[j][i]) {
        return true;
      }
    }
  }
  return false;
}

vector<int> Graph::Neighbors(const int &vertex) const {
  vector<int> result;
  for (int i = 0; i < Size(); ++i) {
    if (adjacency_matrix_[vertex][i] > 0) {
      result.push_back(i);
    }
  }
  return result;
}

vector<int> Graph::NeighborsFromEnd(const int &vertex) const {
  vector<int> result;
  for (int i = Size() - 1; i >= 0; --i) {
    if (adjacency_matrix_[vertex][i] > 0) {
      result.push_back(i);
    }
  }
  return result;
}

void Graph::LoadGraphFromFile(std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw "loadgraphfromfile: wrong file";
  }

  std::string buff_str;
  int vertex_number = 0;
  std::getline(file, buff_str);
  if (sscanf(buff_str.c_str(), "%d", &vertex_number) != 1 ||
      vertex_number <= 0) {
    throw "loadgraphfromfile: wrong file";
  }

  vector<vector<int>> adjacency_matrix;
  int buff_val = 0;
  while (std::getline(file, buff_str)) {
    CheckLineCorrectness(buff_str);
    std::istringstream stream(buff_str);
    std::vector<int> buff_vectr;
    while (!stream.eof()) {
      stream >> buff_val;
      buff_vectr.push_back(buff_val);
    }
    adjacency_matrix.push_back(buff_vectr);
  }
  file.close();

  CheckCorrectness(adjacency_matrix, vertex_number);
  adjacency_matrix_ = adjacency_matrix;
}

void Graph::CheckCorrectness(vector<vector<int>> &vctr, const int &size) const {
  std::size_t sz = static_cast<int>(size);
  if (vctr.size() != sz) {
    throw "loadgraphfromfile: wrong file";
  }
  std::for_each(vctr.begin(), vctr.end(), [sz](const vector<int> &row) {
    if (row.size() != sz) {
      throw "loadgraphfromfile: wrong file";
    }
  });
}

void Graph::CheckLineCorrectness(const std::string &buff_line) const {
  std::for_each(buff_line.begin(), buff_line.end(), [](const char &a) {
    if (a != ' ' && a != 9 && a != '-' && (a > 57 || a < 48)) {
      throw "loadgraphfromfile: wrong file";
    }
  });
}

void Graph::ExportGraphToDot(std::string filename) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    throw "loadgraphfromfile: wrong file";
  }
  Export(file, IsDirected());
  file.close();
}

void Graph::Export(std::ofstream &file, const bool state) const {
  std::string link = (state) ? " -> " : " -- ";
  file << "digraph MyGraph {" << std::endl;
  for (int i = 0; i < Size(); ++i) {
    for (int j = 0; j < Size(); ++j) {
      if (adjacency_matrix_[i][j] > 0) {
        file << "  " << i << link << j;
        ExportEdgeWeight(file, i, j);
      }
    }
  }
  file << "}" << std::endl;
}

void Graph::ExportEdgeWeight(std::ofstream &file, const int &i,
                             const int &j) const {
  if (adjacency_matrix_[i][j] > 0) {
    file << " [label=" << adjacency_matrix_[i][j]
         << "; weight=" << adjacency_matrix_[i][j] << ";]";
  }
  file << ";" << std::endl;
}

void Graph::PrintMatrix() const {
  for (int i = 0; i < Size(); ++i) {
    for (int j = 0; j < Size(); ++j) {
      std::cout << adjacency_matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

} // namespace s21
