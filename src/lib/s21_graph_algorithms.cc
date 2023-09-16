#include "s21_graph_algorithms.h"

#include <algorithm>
#include <cmath>
#include <exception>
#include <functional>
#include <numeric>
#include <random>
#include <vector>

namespace s21 {

vector<int> GraphAlgorithms::DepthFirstSearch(const Graph &graph,
                                              const int start_vertex) {
  if (start_vertex >= graph.Size() || start_vertex < 0) {
    throw "invalid argument";
  }
  vector<bool> visited(graph.Size(), false);
  vector<int> traversed;
  Stack<int> vertex_stack;

  vertex_stack.push(start_vertex);

  while (!vertex_stack.empty()) {
    int vertex = vertex_stack.top();
    vertex_stack.pop();

    if (!visited[vertex]) {
      visited[vertex] = true;
      traversed.push_back(vertex);

      for (int neighbor : graph.NeighborsFromEnd(vertex)) {
        if (!visited[neighbor]) {
          vertex_stack.push(neighbor);
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
  if (start >= graph.Size() || start < 0) {
    throw "invalid argument";
  }
  vector<bool> visited(graph.Size(), false);
  vector<int> traversed;

  Queue<int> vertex_queue;
  vertex_queue.push(start);

  while (!vertex_queue.empty()) {
    int vertex = vertex_queue.front();
    vertex_queue.pop();

    if (!visited[vertex]) {
      visited[vertex] = true;
      traversed.push_back(vertex);

      for (int neighbor : graph.Neighbors(vertex)) {
        if (!visited[neighbor]) {
          vertex_queue.push(neighbor);
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
  if (vertex1 < 1 || vertex1 > graph.Size() || vertex2 < 1 ||
      vertex2 > graph.Size()) {
    throw "";
  }
  vector<int> distance(graph.Size(), kInf);
  vector<bool> visited(graph.Size(), false);
  Queue<int> vertex_queue;

  distance[vertex1 - 1] = 0;
  vertex_queue.push(vertex1 - 1);

  while (!vertex_queue.empty()) {
    int i = vertex_queue.front();
    vertex_queue.pop();

    if (visited[i]) {
      continue;
    }
    visited[i] = true;

    for (int j : graph.Neighbors(i)) {
      int new_distance = distance[i] + graph.GetEdgeWeight(i, j);
      if (new_distance < distance[j]) {
        distance[j] = new_distance;
        vertex_queue.push(j);
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

  vector<vector<int>> spanning_tree(size, vector<int>(size, 0));

  distances[0] = 0;

  for (int i = 0; i < size - 1; ++i) {
    int min_distance = kInf;
    int min_vertex = -1;

    for (int j = 0; j < size; ++j) {
      if (!visited[j] && distances[j] < min_distance) {
        min_distance = distances[j];
        min_vertex = j;
      }
    }

    visited[min_vertex] = true;

    if (parents[min_vertex] != -1) {
      spanning_tree[parents[min_vertex]][min_vertex] =
          graph.GetEdgeWeight(parents[min_vertex], min_vertex);
      spanning_tree[min_vertex][parents[min_vertex]] =
          graph.GetEdgeWeight(parents[min_vertex], min_vertex);
    }

    for (int j = 0; j < size; ++j) {
      if (!visited[j] && graph.GetEdgeWeight(min_vertex, j) > 0 &&
          graph.GetEdgeWeight(min_vertex, j) < distances[j]) {
        parents[j] = min_vertex;
        distances[j] = graph.GetEdgeWeight(min_vertex, j);
      }
    }
  }

  return spanning_tree;
}

vector<vector<double>> GraphAlgorithms::InitializePheromone(int n) {
  if (n < 1) {
    throw "";
  }
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
  double answ_attractivness = 0.0;
  int size = visited.size();
  double sum = 0.0;
  for (int i = 0; i < size; ++i) {
    if (visited[i] == false && (graph.GetEdgeWeight(current, i) > 0)) {
      sum += pow(pheromone[current][i], kAlpha) *
             pow(Eta(current, i, graph), kBeta);
    }
  }

  double buff_attractivness = 0.0;
  for (int i = 0; i < size; ++i) {
    if (visited[i] == false && (graph.GetEdgeWeight(current, i) > 0)) {
      buff_attractivness = pow(pheromone[current][i], kAlpha) *
                           pow(Eta(current, i, graph), kBeta) / sum;
      if (buff_attractivness > answ_attractivness) {
        answ = i;
        answ_attractivness = buff_attractivness;
      }
    }
  }
  return answ;
}

void GraphAlgorithms::UpdatePheromone(vector<vector<double>> &pheromone,
                                      const vector<Ant> &ants,
                                      const Graph &graph) {
  for (auto &start : pheromone) {
    for (auto &road : start) {
      road *= kRHO;
    }
  }

  for (auto &ant : ants) {
    for (auto itr = ant.ant_result_.vertices.begin();
         itr != ant.ant_result_.vertices.end() - 1; ++itr) {
      int start = *itr;
      int end = *(itr + 1);
      pheromone[start][end] += ant.quantity_ / graph.GetEdgeWeight(start, end);
    }
  }
}

Ant GraphAlgorithms::BuildTour(int start, vector<bool> &visited,
                               const vector<vector<double>> &pheromone,
                               const Graph &graph) {
  Ant ant;
  ant.ant_result_.vertices.push_back(start);
  ant.ant_result_.distance = 0.0;
  visited[start] = true;
  int current = start;
  int size = visited.size();
  for (int i = 1; i < size; ++i) {
    int next = -1;
    next = SelectNext(current, visited, pheromone, graph);
    if (next == -1) {
      break;
    }
    ant.ant_result_.vertices.push_back(next);
    ant.ant_result_.distance += graph.GetEdgeWeight(current, next);
    ant.quantity_ += pheromone[current][next];
    visited[next] = true;
    current = next;
  }

  if (graph.GetEdgeWeight(current, start) > 0) {
    ant.ant_result_.vertices.push_back(start);
    ant.ant_result_.distance += graph.GetEdgeWeight(current, start);
    ant.quantity_ += pheromone[current][start];
  }

  return ant;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(const Graph &graph) {
  if (graph.Size() == 0) {
    throw "";
  }
  int n = graph.Size();
  vector<vector<double>> pheromone = InitializePheromone(n);
  TsmResult best_result;
  best_result.distance = std::numeric_limits<double>::max();
  for (int iter = 0; iter < kNumIterations; iter++) {

    std::vector<Ant> ants(kNumAnts);
    std::vector<Ant> succeded_ants;

    std::random_device rd;
    std::default_random_engine engine(rd());
    auto gen = std::bind(std::uniform_int_distribution<>(0, n - 2), engine);

    for (int k = 0; k < kNumAnts; k++) {
      int start = gen();

      std::vector<bool> visited(n, false);
      ants[k] = BuildTour(start, visited, pheromone, graph);
      int size = ants[k].ant_result_.vertices.size();
      if (size == (n + 1)) {
        succeded_ants.push_back(ants[k]);
        if (ants[k].ant_result_.distance <= best_result.distance) {
          best_result = ants[k].ant_result_;
        }
      }
    }
    UpdatePheromone(pheromone, succeded_ants, graph);
  }

  std::for_each(best_result.vertices.begin(), best_result.vertices.end(),
                [](int &x) { ++x; });
  return best_result;
}

} // namespace s21
