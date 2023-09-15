#include "s21_graph_algorithms.h"

#include <algorithm>
#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

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
  if (vertex1 < 1 || vertex1 > graph.Size() ||
      vertex2 < 1 || vertex2 > graph.Size()) {
        throw "";
      }
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


vector<vector<double>> GraphAlgorithms::InitializePheromone(int n) {
  return vector<vector<double>>(n, vector<double>(n, kInitialPheromone));
}


double GraphAlgorithms::Eta(int i, int j, const Graph &graph) {
  return 1.0 / (graph.GetEdgeWeight(i, j));
}


double GraphAlgorithms::Random() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  auto gen = std::bind(std::uniform_real_distribution<>(0, 1), engine);
  return static_cast<double>(gen());
}


int GraphAlgorithms::SelectNext(const int current, const vector<bool> &visited,
                                const vector<vector<double>> &pheromone,
                                const Graph &graph) {
  int answ = -1;
  double answAttractivness = 0.0;
  int size = visited.size();
  double sum = 0.0;
  for (int i = 0; i < size; ++i) {
    if (!visited[i] && (graph.GetEdgeWeight(current, i) > 0)) {
      sum += pow(pheromone[current][i], kAlpha) *
             pow(Eta(current, i, graph), kBeta);
    }
  }

  double buffAttractivness = 0.0;
  for (int i = 0; i < size; ++i) {
    if (!visited[i] && (graph.GetEdgeWeight(current, i) > 0)) {
      buffAttractivness = pow(pheromone[current][i], kAlpha) *
                          pow(Eta(current, i, graph), kBeta) / sum;
      if (buffAttractivness > answAttractivness) {
        answ = i;
        answAttractivness = buffAttractivness;
      }
    }
  }
  return answ;
}


void GraphAlgorithms::UpdatePheromone(vector<vector<double>> &pheromone,
                                      const vector<TsmResult> &ants,
                                      const Graph &graph) {
for (auto & start : pheromone) {
  for (auto & road: start) {
    road *= kRHO;
  }
}

  for (auto &ant : ants) {
    for (auto itr = ant.vertices.begin(); itr != ant.vertices.end() - 1;
         ++itr) {
      int start = *itr;
      int end = *(itr + 1);
      pheromone[start][end] +=
          ant.quantity_ / graph.GetEdgeWeight(start, end);
    }
  }
}


TsmResult GraphAlgorithms::BuildTour(int start, vector<bool> &visited,
                                     const vector<vector<double>> &pheromone,
                                     const Graph &graph) {
  TsmResult ant;
  ant.vertices.push_back(start);
  ant.distance = 0.0;
  visited[start] = true;
  int current = start;
  int size = visited.size();
  for (int i = 1; i < size; ++i) {
    int next = SelectNext(current, visited, pheromone, graph);
    if (next == -1) {
      break;
    }
    ant.vertices.push_back(next);
    ant.distance += graph.GetEdgeWeight(current, next);
    ant.quantity_ += pheromone[current][next];
    visited[next] = true;
    current = next;
  }

  if (graph.GetEdgeWeight(current, start) > 0) {
    ant.vertices.push_back(start);
    ant.distance += graph.GetEdgeWeight(current, start);
    ant.quantity_ += pheromone[current][start];
  }

  return ant;
}


TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(const Graph &graph) {
  int n = graph.Size();
  vector<vector<double>> pheromone = InitializePheromone(n);
  TsmResult best_result;
  best_result.distance = std::numeric_limits<double>::max();
  for (int iter = 0; iter < kNumIterations; iter++) {

    std::vector<TsmResult> ants(kNumAnts);
    std::vector<TsmResult> succededAnts;

    std::random_device rd;
    std::default_random_engine engine(rd());
    auto gen = std::bind(std::uniform_int_distribution<>(0, n - 2), engine);

    for (int k = 0; k < kNumAnts; k++) {
      int start = gen();


      std::vector<bool> visited(n, false);
      ants[k] = BuildTour(start, visited, pheromone, graph);
      int size = ants[k].vertices.size();
      if (size == (n + 1)) {
        succededAnts.push_back(ants[k]);
        if (ants[k].distance <= best_result.distance) {
          best_result = ants[k];
        }
      }
    }
    UpdatePheromone(pheromone, succededAnts, graph);
  }

  std::for_each(best_result.vertices.begin(), best_result.vertices.end(),
                [](int &x) { ++x; });
  return best_result;
}

} // namespace s21
