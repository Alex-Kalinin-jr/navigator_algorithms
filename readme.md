Simple cmd-line application for work with standard graph algorithms, with self-written stack and queue.
The program is written using MVC-pattern. There are classes: 
- "Graph" for data storing, 
- "GraphAlgorithms" with static methods, 
- "View" for interactions with user,
- "Controller" for control of model's and view's behaviour and for their interactions.

All exceptions are handled in "Controller" and do not lead to program termination. Instead messages are appeared for user.
The program conforms to C++17 standard, checked for leaks and heap-errors with walgrind, checked with cppcheck, styled with clang-format (Google-style). 

The next algorithms have been implemented:
- app-key 1: LoadGraphFromFile(string filename).
- app-key 2: DepthFirstSearch(Graph &graph, int start_vertex).
- app-key 3: BreadthFirstSearch(Graph &graph, int start_vertex).
- app-key 4: GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2).
- app-key 5: GetShortestPathsBetweenAllVertices(Graph &graph).
- app-key 6: GetLeastSpanningTree(Graph &graph).
- app-key 7: SolveTravelingSalesmanProblem(Graph &graph).

