#include <algorithm>
#include <vector>

#include "lib/s21_graph.h"
#include "lib/s21_graph_algorithms.h"
#include "lib/s21_queue.h"
#include "lib/s21_stack.h"
#include "gtest/gtest.h"

using s21::Graph;
using s21::GraphAlgorithms;
using std::vector;

bool CompareVectorsContent(std::vector<int> &a, std::vector<int> &b) {
  bool state = true;
  std::for_each(a.begin(), a.end(), [&b, &state](int &node) mutable {
    if (std::find(b.begin(), b.end(), node) == b.end()) {
      state = false;
    }
  });
  return state;
}

TEST(ExportGraphToDot, aa) {
  Graph test_graph;
  test_graph.LoadGraphFromFile(
      "tests/examples/unweighted_undirected_graph.txt");
  test_graph.ExportGraphToDot("tests/unweighted_undirected_graph.dot");
  test_graph.PrintMatrix();
}

TEST(ExportGraphToDot, ac) {
  Graph test_graph;
  EXPECT_ANY_THROW(test_graph.LoadGraphFromFile("tests/wrong_size_2.txt"););
}

TEST(ExportGraphToDot, ad) {
  Graph test_graph;
  EXPECT_ANY_THROW(test_graph.LoadGraphFromFile("tests/wrong_size_3.txt"););
}

TEST(ExportGraphToDot, ae) {
  Graph test_graph;
  EXPECT_ANY_THROW(test_graph.LoadGraphFromFile("tests/wrong_data_1.txt"););
}

TEST(ExportGraphToDot, af) {
  Graph test_graph;
  EXPECT_ANY_THROW(test_graph.LoadGraphFromFile("tests/wrong_data_2.txt"););
}

TEST(ExportGraphToDot, ag) {
  Graph test_graph;
  EXPECT_ANY_THROW(test_graph.LoadGraphFromFile("tests/wrong_data_3.txt"););
}

TEST(ExportGraphToDot, UnweightedDirectedGraph) {
  Graph test_graph;
  test_graph.LoadGraphFromFile("tests/examples/unweighted_directed_graph.txt");
  test_graph.PrintMatrix();
  test_graph.ExportGraphToDot("tests/unweighted_directed_graph.dot");
}

TEST(ExportGraphToDot, udg2) {
  Graph test_graph;
  test_graph.LoadGraphFromFile("tests/examples/udg_2.txt");
  test_graph.PrintMatrix();
  test_graph.ExportGraphToDot("tests/udg_2.dot");
}

TEST(LoadGraphFromFile, WeightedDirectedGraph) {
  Graph test_graph;
  test_graph.LoadGraphFromFile("tests/examples/weighted_undirected_graph.txt");
  vector<vector<int>> excepted = {{0, 29, 20, 21, 16, 31, 100, 12, 4, 31, 18},
                                  {29, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12},
                                  {20, 15, 0, 15, 14, 25, 81, 9, 23, 27, 13},
                                  {21, 29, 15, 0, 4, 12, 92, 12, 25, 13, 25},
                                  {16, 28, 14, 4, 0, 16, 94, 9, 20, 16, 22},
                                  {31, 40, 25, 12, 16, 0, 95, 24, 36, 3, 37},
                                  {100, 72, 81, 92, 94, 95, 0, 90, 101, 99, 84},
                                  {12, 21, 9, 12, 9, 24, 90, 0, 15, 25, 13},
                                  {4, 29, 23, 25, 20, 36, 101, 15, 0, 35, 18},
                                  {31, 41, 27, 13, 16, 3, 99, 25, 35, 0, 38},
                                  {18, 12, 13, 25, 22, 37, 84, 13, 18, 38, 0}};
  for (unsigned i = 0; i < excepted.size(); ++i)
    for (unsigned j = 0; j < excepted[i].size(); ++j) {
      EXPECT_EQ(excepted[i][j], test_graph.GetEdgeWeight(i, j));
    }
}

TEST(stack, create) {
  s21::Stack<int> a;
  s21::Stack<int> b({1, 2, 3, 4});
  s21::Stack<int> c(b);
  s21::Stack<int> d;
  d = c;
  s21::Stack<int> e = s21::Stack<int>({1, 3, -5});
  a = s21::Stack<int>(b);
}

TEST(stack, operations) {
  s21::Stack<int> a;
  ASSERT_TRUE(a.empty());
  for (int i = 0; i < 1000000; ++i) {
    a.push(i);
  }
  ASSERT_EQ(a.top(), 999999);
  ASSERT_EQ(a.size(), 1000000);
}

TEST(stack, operations2) {
  s21::Stack<int> a{3, 4, 5};
  ASSERT_FALSE(a.empty());
  for (int i = 0; i < 1000000; ++i) {
    a.push(i);
  }
  ASSERT_EQ(a.top(), 999999);
  for (int i = 0; i < 50; ++i) {
    a.pop();
    ASSERT_EQ(a.top(), 999999 - i - 1);
  }
}

TEST(stack, operations3) {
  s21::Stack<int> a{3, 4, 5};
  s21::Stack<int> b{2, 6, 8};
  s21::Stack<int> c(a);
  s21::Stack<int> d(b);
  c.swap(b);
  d.swap(a);
  ASSERT_EQ(c.top(), 8);
  ASSERT_EQ(d.top(), 5);
}

TEST(queue, create) {
  s21::Queue<int> a;
  s21::Queue<int> b({1, 2, 3, 4});
  s21::Queue<int> c(b);
  s21::Queue<int> d;
  d = c;
  s21::Queue<int> e = s21::Queue<int>({1, 3, -5});
  a = s21::Queue<int>(b);
}

TEST(queue, operations) {
  s21::Queue<int> a;
  ASSERT_TRUE(a.empty());
  for (int i = 0; i < 1000000; ++i) {
    a.push(i);
  }
  ASSERT_EQ(a.back(), 999999);
  ASSERT_EQ(a.size(), 1000000);
  ASSERT_EQ(a.front(), 0);
}

TEST(queue, operations2) {
  s21::Queue<int> a;
  for (int i = 0; i < 1000000; ++i) {
    a.push(i);
  }
  ASSERT_EQ(a.back(), 999999);

  for (int i = 0; i < 50; ++i) {
    a.pop();
    ASSERT_EQ(a.back(), 999999);
    ASSERT_EQ(a.front(), 0 + i + 1);
  }
}

TEST(queue, operations3) {
  s21::Queue<int> a{3, 4, 5};
  s21::Queue<int> b{2, 6, 8};
  s21::Queue<int> c(a);
  s21::Queue<int> d(b);
  c.swap(b);
  d.swap(a);
  ASSERT_EQ(c.back(), 8);
  ASSERT_EQ(d.back(), 5);
}

TEST(DepthFirstSearchTest, udg2) {
  Graph test_graph;
  test_graph.LoadGraphFromFile("tests/examples/undirected_graph.txt");
  vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  vector<int> actual = GraphAlgorithms::DepthFirstSearch(test_graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
  ASSERT_TRUE(CompareVectorsContent(expected, actual));
}

TEST(DepthFirstSearchTest, dg1) {
  Graph test_graph;
  test_graph.LoadGraphFromFile("tests/examples/unweighted_directed_graph.txt");
  vector<int> expected = {1, 2, 3, 4, 5};
  vector<int> actual = GraphAlgorithms::DepthFirstSearch(test_graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
  ASSERT_TRUE(CompareVectorsContent(expected, actual));
}

TEST(DepthFirstSearchTest, uug1) {
  Graph test_graph;
  test_graph.LoadGraphFromFile(
      "tests/examples/unweighted_undirected_graph.txt");
  vector<int> expected = {1, 2, 4, 3, 5, 6};
  vector<int> actual = GraphAlgorithms::DepthFirstSearch(test_graph, 0);
  ASSERT_TRUE(CompareVectorsContent(expected, actual));
}

TEST(DepthFirstSearchTest, wug1) {
  Graph test_graph;
  test_graph.LoadGraphFromFile("tests/examples/weighted_undirected_graph.txt");
  vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  vector<int> actual = GraphAlgorithms::DepthFirstSearch(test_graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
  ASSERT_TRUE(CompareVectorsContent(expected, actual));
}

TEST(BreadthFirstSearch, udg2) {
  Graph test_graph;
  test_graph.LoadGraphFromFile("tests/examples/undirected_graph.txt");
  vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  vector<int> actual = GraphAlgorithms::BreadthFirstSearch(test_graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
  ASSERT_TRUE(CompareVectorsContent(expected, actual));
}

TEST(BreadthFirstSearch, dg1) {
  Graph test_graph;
  test_graph.LoadGraphFromFile("tests/examples/unweighted_directed_graph.txt");
  vector<int> expected = {1, 2, 3, 4, 5};
  vector<int> actual = GraphAlgorithms::BreadthFirstSearch(test_graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
  ASSERT_TRUE(CompareVectorsContent(expected, actual));
}

TEST(BreadthFirstSearch, uug1) {
  Graph test_graph;
  test_graph.LoadGraphFromFile(
      "tests/examples/unweighted_undirected_graph.txt");
  vector<int> expected = {1, 2, 4, 3, 5, 6};
  vector<int> actual = GraphAlgorithms::BreadthFirstSearch(test_graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
  ASSERT_TRUE(CompareVectorsContent(expected, actual));
}

TEST(BreadthFirstSearch, wug1) {
  Graph test_graph;
  test_graph.LoadGraphFromFile("tests/examples/weighted_undirected_graph.txt");
  vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  vector<int> actual = GraphAlgorithms::BreadthFirstSearch(test_graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
  ASSERT_TRUE(CompareVectorsContent(expected, actual));
}

TEST(GetShortestPathBetweenVertices, UnweightedDirectedGraph) {
  Graph graph;
  graph.LoadGraphFromFile("tests/examples/unweighted_directed_graph.txt");

  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 3), 3);
}

TEST(GetShortestPathBetweenVertices, dwg) {
  Graph graph;
  graph.LoadGraphFromFile("tests/examples/dwg.txt");
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 4), 3);
}

TEST(GetShortestPathBetweenVertices, dwg2) {
  Graph graph;
  graph.LoadGraphFromFile("tests/examples/dwg2.txt");
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 4), 2);
}

TEST(GetShortestPathsBetweenAllVertices, udg1) {
  Graph graph;
  graph.LoadGraphFromFile("tests/examples/unweighted_directed_graph.txt");

  vector<vector<int>> expected = {{2, 1, 3, 1, 2},
                                  {2, 1, 3, 1, 2},
                                  {1, 2, 2, 1, 1},
                                  {1, 2, 2, 2, 1},
                                  {1, 2, 1, 2, 1}};

  vector<vector<int>> actual =
      GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);

  ASSERT_EQ(expected, actual);
}

TEST(GetShortestPathsBetweenAllVertices, uug) {
  Graph graph;
  graph.LoadGraphFromFile("tests/examples/uug.txt");
  vector<vector<int>> actual =
      GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);

  ASSERT_EQ(actual[0][4], 11);
}

TEST(GetLeastSpanningTree, UnweightedDirectedGraph) {
  Graph graph;
  graph.LoadGraphFromFile("tests/examples/unweighted_directed_graph.txt");
  vector<vector<int>> expected_result = {{0, 1, 0, 1, 0},
                                         {1, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                         {1, 0, 0, 0, 1},
                                         {0, 0, 0, 1, 0}};

  vector<vector<int>> actual_result =
      GraphAlgorithms::GetLeastSpanningTree(graph);

  EXPECT_EQ(actual_result, expected_result);
}

TEST(SolveTravelingSalesmanProblem, WeightedUndirectedGraph) {
  Graph test_graph;
  s21::TsmResult result;
  test_graph.LoadGraphFromFile("tests/examples/weighted_undirected_graph.txt");
  result = GraphAlgorithms::SolveTravelingSalesmanProblem(test_graph);
  EXPECT_LE(result.distance, 255);
}

TEST(SolveTravelingSalesmanProblem, wug2) {
  Graph test_graph;
  s21::TsmResult result;
  test_graph.LoadGraphFromFile("tests/examples/wug2.txt");
  result = GraphAlgorithms::SolveTravelingSalesmanProblem(test_graph);
  s21::TsmResult expected = {{1, 3, 4, 2, 1}, 80};
  EXPECT_EQ(result.distance, expected.distance);
}

TEST(SolveTravelingSalesmanProblem, wug3) {
  Graph test_graph;
  s21::TsmResult result;
  test_graph.LoadGraphFromFile("tests/examples/wug3.txt");
  result = GraphAlgorithms::SolveTravelingSalesmanProblem(test_graph);
  s21::TsmResult expected = {{1, 4, 5, 2, 3, 1}, 48};
  EXPECT_EQ(result.distance, expected.distance);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
