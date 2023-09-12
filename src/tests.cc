#include <vector>

#include "lib/s21_graph.h"
// #include "lib/s21_graph_algorithms.h"
#include "gtest/gtest.h"
#include "lib/s21_stack.h"
#include "lib/s21_queue.h"

using s21::Graph;
// using s21::GraphAlgorithms;
using std::vector;

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
  s21::Stack<int>c(b);
  s21::Stack<int>d;
  d = c;
  s21::Stack<int> e = s21::Stack<int>({1, 3, -5});
  a = s21::Stack<int>(b);
  s21::Stack<int>f(s21::Stack<int>({1, 2, 3}));
  s21::Stack<int>g(s21::Stack<int>(b));
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
  s21::Stack<int> a {3, 4, 5};
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
  s21::Stack<int> a {3, 4, 5};
  s21::Stack<int> b {2, 6, 8};
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
  s21::Queue<int>c(b);
  s21::Queue<int>d;
  d = c;
  s21::Queue<int> e = s21::Queue<int>({1, 3, -5});
  a = s21::Queue<int>(b);
  s21::Queue<int>f(s21::Queue<int>({1, 2, 3}));
  s21::Queue<int>g(s21::Queue<int>(b));
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
  s21::Queue<int> a {3, 4, 5};
  s21::Queue<int> b {2, 6, 8};
  s21::Queue<int> c(a);
  s21::Queue<int> d(b);
  c.swap(b);
  d.swap(a);
  ASSERT_EQ(c.back(), 8);
  ASSERT_EQ(d.back(), 5);
}



// TEST(DepthFirstSearchTest, UnweightedUndirectedGraph) {
//   Graph test_graph;
//   test_graph.LoadGraphFromFile(
//       "tests/examples/unweighted_undirected_graph.txt");
//   vector<int> expected_traversal = {1, 2, 4, 3, 5, 6};
//   vector<int> actual_traversal =
//       GraphAlgorithms::DepthFirstSearch(test_graph, 0);

//   EXPECT_EQ(actual_traversal, expected_traversal);
// }

// TEST(BreadthFirstSearchTest, UnweightedUndirectedGraph) {
//   Graph test_graph;
//   test_graph.LoadGraphFromFile(
//       "tests/examples/unweighted_undirected_graph.txt");
//   vector<int> expected_traversal = {1, 2, 3, 4, 5, 6};
//   vector<int> actual_traversal =
//       GraphAlgorithms::BreadthFirstSearch(test_graph, 0);

//   EXPECT_EQ(actual_traversal, expected_traversal);
// }

// TEST(GetShortestPathBetweenVertices, UnweightedDirectedGraph) {
//   Graph graph;
//   graph.LoadGraphFromFile("tests/examples/unweighted_directed_graph.txt");

//   EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 3), 3);
// }

// TEST(GetShortestPathsBetweenAllVertices, UnweightedDirectedGraph) {
//   Graph graph;
//   graph.LoadGraphFromFile("tests/examples/unweighted_directed_graph.txt");

//   vector<vector<int>> expected_distances = {{2, 1, 3, 1, 2},
//                                             {2, 1, 3, 1, 2},
//                                             {1, 2, 2, 1, 1},
//                                             {1, 2, 2, 2, 1},
//                                             {1, 2, 1, 2, 1}};

//   vector<vector<int>> actual_distances =
//       GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);

//   ASSERT_EQ(expected_distances, actual_distances);
// }

// TEST(GetLeastSpanningTree, UnweightedDirectedGraph) {
//   Graph graph;
//   graph.LoadGraphFromFile("tests/examples/unweighted_directed_graph.txt");
//   vector<vector<int>> expected_result = {{0, 1, 0, 1, 0},
//                                          {1, 0, 0, 0, 0},
//                                          {0, 0, 0, 0, 0},
//                                          {1, 0, 0, 0, 1},
//                                          {0, 0, 0, 1, 0}};

//   vector<vector<int>> actual_result =
//       GraphAlgorithms::GetLeastSpanningTree(graph);

//   EXPECT_EQ(actual_result, expected_result);
// }

// TEST(SolveTravelingSalesmanProblem, WeightedUndirectedGraph) {
//   Graph test_graph;
//   s21::TsmResult result;
//   test_graph.LoadGraphFromFile("tests/examples/weighted_undirected_graph.txt");
//   result = GraphAlgorithms::SolveTravelingSalesmanProblem(test_graph);

//   s21::TsmResult expected = {{1, 8, 5, 4, 10, 6, 3, 7, 2, 2, 11, 9}, 253};

//   EXPECT_EQ(result.distance, expected.distance);
//   EXPECT_EQ(result.vertices, expected.vertices);
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
