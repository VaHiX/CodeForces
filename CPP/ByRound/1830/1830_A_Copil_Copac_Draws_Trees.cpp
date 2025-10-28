// Problem: CF 1830 A - Copil Copac Draws Trees
// https://codeforces.com/contest/1830/problem/A

/*
A. Copil Copac Draws Trees

Algorithms/Techniques: DFS traversal, Tree traversal simulation

Time Complexity: O(n) per test case, where n is the number of vertices.
Space Complexity: O(n) for storing the tree structure and recursion stack.

This problem simulates a process where edges are processed in order to build a tree,
starting from vertex 1. During each "reading", all unvisited neighbors of already visited
vertices are explored. The number of readings corresponds to how many times we must
process the entire edge list before the whole tree is drawn.
*/

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

const int N = 2e5 + 5;
int n, mx;
std::vector<std::pair<int, int>> e[N]; // adjacency list, storing {neighbor, edge_id}

void dfs(int x, int fa, int d, int fr = n) {
  mx = std::max(mx, d); // update maximum depth (number of readings)
  for (auto [y, z] : e[x]) // iterate through neighbors
    if (y != fa) // avoid going back to parent
      dfs(y, x, d + (z < fr), z); // recursive call with updated depth and edge reference
}

void ans() {
  scanf("%d", &n), mx = 0; // read number of nodes, reset max depth
  for (int i = 1, x, y; i < n; ++i) { // read each edge
    scanf("%d%d", &x, &y);
    e[x].emplace_back(y, i); // add edge from x to y with id i
    e[y].emplace_back(x, i); // add edge from y to x with id i
  }
  dfs(1, 0, 0); // start DFS from node 1 with initial depth 0
  printf("%d\n", mx); // print result
  for (int i = 1; i <= n; ++i) // clear adjacency lists for next test case
    e[i].clear();
}

int main() {
  int T;
  for (scanf("%d", &T); T--;) // process all test cases
    ans();
  return 0;
}


// https://github.com/VaHiX/codeForces/