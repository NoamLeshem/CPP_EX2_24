# CPP EX1 - Graph and Algorithms

## Table of Contents

- [CPP EX1 - Graph and Algorithms](#cpp-ex1---graph-and-algorithms)
  - [Table of Contents](#table-of-contents)
  - [Graph](#graph)
  - [Algorithms](#algorithms)
  - [How to Use](#how-to-use)

## Graph

`Graph.cpp` מימוש של מחקלת הגרף

## Algorithms

`Algorithms.cpp` מימוש של אלגוריתמים שונים המתבצעים על גרף

## How to Use

1. **Include Header Files:**

   ```cpp
   #include "Graph.hpp"
   #include "Algorithms.hpp"
   ```

2. **Namespace Usage:**

   ```cpp
   using namespace ariel;
   ```

3. **Creating a Graph:**

   ```cpp
   Graph g;
   ```

4. **Loading:**

   ```cpp
   vector<vector<int>> graph = {
       {0, 1, 0},
       {1, 0, 1},
       {0, 1, 0}};
   g.loadGraph(graph);
   ```

5. **Algorithms:**

   ```cpp
   isConnected(g);
   shortestPath(g, 0, 2);
   isContainsCycle(g);
   isBipartite(g);
   ```
