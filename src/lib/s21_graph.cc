#include "s21_graph.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
#include <string>
#include <sstream>

namespace s21 {

int Graph::GetEdgeWeight(int i, int j) const { return adjacency_matrix_[i][j]; }

int Graph::Size() const { return static_cast<int>(adjacency_matrix_.size()); }

int Graph::Size(int i) const {
  return static_cast<int>(adjacency_matrix_[i].size());
}

bool Graph::IsDirected() {
  for (int i = 0; i < Size(); ++i) {
    for (int j = i + 1; j < Size(i); ++j) {
      if (adjacency_matrix_[i][j] != adjacency_matrix_[j][i]) {
        return true;
      }
    }
  }
  return false;
}

vector<int> Graph::Neighbors(int vertex) const {
  vector<int> result;
  for (int i = 0; i < Size(); ++i) {
    if (adjacency_matrix_[vertex][i] > 0) {
      result.push_back(i);
    }
  }
  return result;
}

vector<int> Graph::NeighborsFromEnd(int vertex) const {
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

  std::string buffStr;
  int vertexNumber = 0;
  std::getline(file, buffStr);
  if (sscanf(buffStr.c_str(), "%d", &vertexNumber) != 1) {
    throw "loadgraphfromfile: wrong file";
  }
  if (vertexNumber <= 0) {
    throw "loadgraphfromfile: wrong file";
  }

  vector<vector<int>> adjacencyMatrix;
  int buffVal = 0;
  while (std::getline(file, buffStr)) {
    std::for_each(buffStr.begin(), buffStr.end(), [](char &a) {
      if (a != ' ' && a != '-' && (a > 57 || a < 48 )) {
        throw "loadgraphfromfile: wrong file";
      }
    });
    std::istringstream stream(buffStr);
    std::vector<int> buffVectr;
    while (!stream.eof()) {
      stream >> buffVal;
      buffVectr.push_back(buffVal);
    }
    adjacencyMatrix.push_back(buffVectr);
  }
  file.close();

  CheckCorrectness(adjacencyMatrix, vertexNumber);
  adjacency_matrix_ = adjacencyMatrix;
}


void Graph::CheckCorrectness(vector<vector<int>> &vctr, int &size) const {
  std::size_t sz = static_cast<int>(size);
  if (vctr.size() != sz) {
    throw "loadgraphfromfile: wrong file";
  }
  std::for_each(vctr.begin(), vctr.end(), [sz](vector<int> &row) {
    if (row.size() != sz) {
      throw "loadgraphfromfile: wrong file";
    }
  });
}


void Graph::ExportGraphToDot(std::string filename) {
  std::ofstream file;
  file.open(filename);
  if (!file.is_open()) {
    std::cerr << "Error: cannot write file " << filename << std::endl;
  }

  if (IsDirected()) {
    ExportDirected(file);
  } else {
    ExportUndirected(file);
  }
  file << "}\n";
  file.close();

  std::cout << "calling ExportGraphToDot function\n";
}

void Graph::ExportDirected(std::ofstream &file) {
  file << "digraph MyGraph {\n";
  for (int i = 0; i < Size(); ++i) {
    for (int j = 0; j < Size(i); ++j) {
      if (adjacency_matrix_[i][j] > 0) {
        file << "  " << i << " -> " << j;
        ExportEdgeWeight(file, i, j);
      }
    }
  }
}

void Graph::ExportUndirected(std::ofstream &file) {
  file << "graph MyGraph {\n";
  for (int i = 0; i < Size(); ++i) {
    for (int j = i + 1; j < Size(i); ++j) {
      if (adjacency_matrix_[i][j] > 0) {
        file << "  " << i << " -- " << j;
        ExportEdgeWeight(file, i, j);
      }
    }
  }
}

void Graph::ExportEdgeWeight(std::ofstream &file, int i, int j) {
  if (adjacency_matrix_[i][j] > 0) {
    file << " [label=" << adjacency_matrix_[i][j]
         << "; weight=" << adjacency_matrix_[i][j] << ";]";
  }
  file << ";\n";
}

}  // namespace s21
