// Problem: CF 1829 F - Forever Winter
// https://codeforces.com/contest/1829/problem/F

/*
F. Forever Winter
Purpose: Given a snowflake graph, determine the values of x and y such that the graph follows the structure:
         - One central vertex
         - x new vertices connected to the central vertex
         - y new vertices connected to each of those x vertices
Algorithms/Techniques: Graph traversal, degree analysis
Time Complexity: O(n + m) per test case, where n is number of vertices and m is number of edges
Space Complexity: O(n + m) for storing the adjacency list representation of the graph

The code analyzes the degree of vertices in the graph:
- A vertex with degree 1 is a leaf (part of y-level)
- A vertex connected to a leaf is a middle node (connected to x-level)
- The central node has degree x
- Each node on the x-level has degree y + 1 since it connects to one central and y leaves
*/

#include <cstdio>
#include <vector>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<std::vector<long>> g(n + 1); // Adjacency list for the graph
    for (long p = 0; p < m; p++) {
      long a, b;
      scanf("%ld %ld", &a, &b);
      g[a].push_back(b);
      g[b].push_back(a);
    }
    long x(0), y(0); // x is the number of vertices connected to the center, y is the number of vertices connected to each x-level vertex
    for (long p = 1; !y && p <= n; p++) {
      if (g[p].size() == 1) { // Found a leaf vertex (degree 1)
        long middle = g[p][0]; // Get the vertex it's connected to (middle node)
        y = g[middle].size() - 1; // Subtract 1 to exclude itself, now we have y
        for (long q = 0; !x && q < g[middle].size(); q++) {
          long center = g[middle][q]; // Get vertex connected to middle
          if (g[center].size() == 1) { // Skip leaves of middle level
            continue;
          }
          x = g[center].size(); // This gives us x, which is the degree of the central node
        }
      }
    }
    printf("%ld %ld\n", x, y);
  }
}


// https://github.com/VaHiX/codeForces/