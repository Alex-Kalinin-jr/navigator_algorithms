#include "s21_graph_algorithms.h"

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <numeric>
#include <vector>
#include <random>
#include <functional>

namespace s21 {

vector<int> GraphAlgorithms::DepthFirstSearch(const Graph &graph,
                                              const int startVertex) {
  if (startVertex >= graph.Size()) {
    throw "invalid argument";
  }
  vector<bool> visited(graph.Size(), false);
  vector<int> traversed;
  Stack<int> vertexStack;

  vertexStack.push(startVertex);

  while (!vertexStack.empty()) {
    int vertex = vertexStack.top();
    vertexStack.pop();

    if (!visited[vertex]) {
      visited[vertex] = true;
      traversed.push_back(vertex);

      for (int neighbor : graph.NeighborsFromEnd(vertex)) {
        if (!visited[neighbor]) {
          vertexStack.push(neighbor);
        }
      }
    }
  }

  std::transform(traversed.begin(), traversed.end(), traversed.begin(),
                 [](int &vertice) -> int {
                   ++vertice;
                   return vertice;
                 });
  return traversed;
}

vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph &graph, int start) {
  if (start >= graph.Size()) {
    throw "invalid argument";
  }
  vector<bool> visited(graph.Size(), false);
  vector<int> traversed;

  Queue<int> vertexQueue;
  vertexQueue.push(start);

  while (!vertexQueue.empty()) {
    int vertex = vertexQueue.front();
    vertexQueue.pop();

    if (!visited[vertex]) {
      visited[vertex] = true;
      traversed.push_back(vertex);

      for (int neighbor : graph.Neighbors(vertex)) {
        if (!visited[neighbor]) {
          vertexQueue.push(neighbor);
        }
      }
    }
  }
  std::transform(traversed.begin(), traversed.end(), traversed.begin(),
                 [](int &vertice) -> int {
                   ++vertice;
                   return vertice;
                 });
  return traversed;
}

int GraphAlgorithms::GetShortestPathBetweenVertices(const Graph &graph,
                                                    const int vertex1,
                                                    const int vertex2) {
  vector<int> distance(graph.Size(), kInf);
  vector<bool> visited(graph.Size(), false);
  Queue<int> vertexQueue;

  distance[vertex1 - 1] = 0;
  vertexQueue.push(vertex1 - 1);

  while (!vertexQueue.empty()) {
    int i = vertexQueue.front();
    vertexQueue.pop();

    if (visited[i]) {
      continue;
    }
    visited[i] = true;

    for (int j : graph.Neighbors(i)) {
      int new_distance = distance[i] + graph.GetEdgeWeight(i, j);
      if (new_distance < distance[j]) {
        distance[j] = new_distance;
        vertexQueue.push(j);
      }
    }
  }
  return distance[vertex2 - 1];
}

vector<vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(const Graph &graph) {
  int count = graph.Size();
  vector<vector<int>> distances(count, vector<int>(count, kInf));

  for (int i = 0; i < count; ++i) {
    for (int j = 0; j < count; ++j) {
      if (graph.GetEdgeWeight(i, j) > 0) {
        distances[i][j] = graph.GetEdgeWeight(i, j);
      }
    }
  }

  for (int k = 0; k < count; ++k) {
    for (int i = 0; i < count; ++i) {
      for (int j = 0; j < count; ++j) {
        if (distances[i][k] != kInf && distances[k][j] != kInf) {
          distances[i][j] =
              std::min(distances[i][j], distances[i][k] + distances[k][j]);
        }
      }
    }
  }

  return distances;
}

vector<vector<int>> GraphAlgorithms::GetLeastSpanningTree(const Graph &graph) {
  int size = graph.Size();
  vector<bool> visited(size, false);
  vector<int> distances(size, kInf);
  vector<int> parents(size, -1);

  vector<vector<int>> spanningTree(size, vector<int>(size, 0));

  distances[0] = 0;

  for (int i = 0; i < size - 1; ++i) {
    int minDistance = kInf;
    int minVertex = -1;

    for (int j = 0; j < size; ++j) {
      if (!visited[j] && distances[j] < minDistance) {
        minDistance = distances[j];
        minVertex = j;
      }
    }

    visited[minVertex] = true;

    if (parents[minVertex] != -1) {
      spanningTree[parents[minVertex]][minVertex] =
          graph.GetEdgeWeight(parents[minVertex], minVertex);
      spanningTree[minVertex][parents[minVertex]] =
          graph.GetEdgeWeight(parents[minVertex], minVertex);
    }

    for (int j = 0; j < size; ++j) {
      if (!visited[j] && graph.GetEdgeWeight(minVertex, j) > 0 &&
          graph.GetEdgeWeight(minVertex, j) < distances[j]) {
        parents[j] = minVertex;
        distances[j] = graph.GetEdgeWeight(minVertex, j);
      }
    }
  }

  return spanningTree;
}

//************************************************************************
//************************************************************************
double GraphAlgorithms::Distance(int i, int j, const Graph &graph) {
  int res = graph.GetEdgeWeight(i, j);
  return res;
}

double GraphAlgorithms::Eta(int i, int j, const Graph &graph) {
  return 1.0 / Distance(i, j, graph);
}

vector<vector<double>> GraphAlgorithms::InitializePheromone(int n) {
  return vector<vector<double>>(n, vector<double>(n, kInitialPheromone));
}

void GraphAlgorithms::UpdatePheromone(vector<vector<double>> &pheromone,
                                      const vector<TsmResult> &ants) {
  for (auto &row : pheromone) {
    for (auto &cell : row) {
      cell *= (1.0 - kRHO);
    }
  }
  for (const TsmResult &ant : ants) {
    double delta = kQ / ant.distance;
    for (int i = 0; i < static_cast<int>(ant.vertices.size()) - 1; i++) {
      int u = ant.vertices[i];
      int v = ant.vertices[i + 1];
      pheromone[u][v] += delta;
      pheromone[v][u] += delta;
    }
  }
}

double GraphAlgorithms::Random() { 
  std::random_device rd;
  std::default_random_engine engine(rd());
  auto gen = std::bind(std::uniform_real_distribution<>(0, 1), engine);
  return static_cast<double>(gen());
}

int GraphAlgorithms::SelectNext(int current, const vector<bool> &visited,
                                const vector<vector<double>> &pheromone,
                                const Graph &graph) {
  int n = visited.size();
  double sum = 0.0;
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      sum += pow(pheromone[current][i], kAlpha) *
             pow(Eta(current, i, graph), kBeta);
    }
  }
  double r = Random() * sum;
  double partial = 0.0;
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      partial += pow(pheromone[current][i], kAlpha) *
                 pow(Eta(current, i, graph), kBeta);
      if (partial >= r) {
        return i;
      }
    }
  }
  return -1;
}

TsmResult GraphAlgorithms::BuildTour(int start, vector<bool> &visited,
                                     const vector<vector<double>> &pheromone,
                                     const Graph &graph) {
  TsmResult result;
  result.vertices.push_back(start);
  result.distance = 0.0;
  visited[start] = true;
  int current = start;
  int n = visited.size();
  for (int i = 1; i < n; i++) {
    int next = SelectNext(current, visited, pheromone, graph);
    result.vertices.push_back(next);
    result.distance += Distance(current, next, graph);
    visited[next] = true;
    current = next;
  }
  result.vertices.push_back(start);
  result.distance += Distance(current, start, graph);
  return result;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(const Graph &graph) {
  int n = graph.Size();
  std::cout << n;
  vector<vector<double>> pheromone = InitializePheromone(n);
  TsmResult best_result;
  best_result.distance = std::numeric_limits<double>::max();
  for (int iter = 0; iter < kNumIterations; iter++) {
    std::vector<TsmResult> ants(kNumAnts);
    for (int k = 0; k < kNumAnts; k++) {
      int start = rand() % (n - 1);
      std::vector<bool> visited(n, false);
      ants[k] = BuildTour(start, visited, pheromone, graph);
      if (ants[k].distance <= best_result.distance) {
        best_result = ants[k];
      }
    }
    UpdatePheromone(pheromone, ants);
  }
  int zero_index =
      std::find(best_result.vertices.begin(), best_result.vertices.end(), 0) -
      best_result.vertices.begin();
  std::rotate(best_result.vertices.begin(),
              best_result.vertices.begin() + zero_index,
              best_result.vertices.end());
  std::for_each(best_result.vertices.begin(), best_result.vertices.end(),
                [](int &x) { ++x; });
  return best_result;
}

} // namespace s21
