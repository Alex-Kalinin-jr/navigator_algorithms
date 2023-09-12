#include "s21_graph.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <exception>

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
  std::cout<<filename<<std::endl;
  if (!file.is_open()) {
    throw "loadgraphfromfile: wrong file";
  }

  int vertex_number;
  file >> vertex_number;

  vector<vector<int>> adjacency_matrix(vertex_number,
                                       vector<int>(vertex_number));
  for (int i = 0; i < vertex_number; ++i) {
    for (int j = 0; j < vertex_number; ++j) {
      file >> adjacency_matrix[i][j];
    }
  }

  adjacency_matrix_ = adjacency_matrix;
  file.close();
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
