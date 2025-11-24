// Problem: CF 691 D - Swaps in Permutation
// https://codeforces.com/contest/691/problem/D

/*
 * Purpose: To find the lexicographically maximal permutation possible by swapping
 * elements at given positions. The allowed swaps form a graph where nodes are
 * indices and edges represent valid swaps.
 * 
 * Algorithm: 
 * 1. Build an undirected graph from the given pairs of positions.
 * 2. Find connected components (using DFS).
 * 3. For each component, collect the values at those indices, sort them in
 *    descending order, and assign them back to the indices in the same component.
 * 
 * Time Complexity: O(n log n + m), where n is the size of the permutation and m is
 * the number of swaps. Sorting contributes O(n log n) and building graph + DFS is O(n + m).
 * 
 * Space Complexity: O(n + m), for storing the graph and auxiliary data structures.
 */

#include <algorithm>
#include <cstdio>
#include <vector>

// Depth First Search to find all nodes reachable from a node
void dfs(long node, const std::vector<std::vector<long>> &g,
         std::vector<bool> &visited, std::vector<long> &group) {
  if (visited[node]) {
    return;
  }
  visited[node] = 1;
  group.push_back(node);
  for (long p = 0; p < g[node].size(); p++) {
    long u = g[node][p];
    if (visited[u]) {
      continue;
    }
    dfs(u, g, visited, group);
  }
  return;
}

int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<std::vector<long>> g(n);
  for (long p = 0; p < m; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    --x; // Convert to 0-based indexing
    --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  std::vector<bool> mark(n, 0); // Track visited nodes
  for (long p = 0; p < n; p++) {
    if (mark[p]) {
      continue;
    }
    std::vector<long> linked; // Store indices in connected component
    dfs(p, g, mark, linked);
    long s = linked.size();
    std::vector<long> values(s);
    for (long q = 0; q < s; q++) {
      values[q] = a[linked[q]]; // Collect values at these indices
    }
    sort(linked.begin(), linked.end());
    sort(values.begin(), values.end());
    for (long q = 0; q < s; q++) {
      a[linked[q]] = values[s - 1 - q]; // Assign sorted values in descending order
    }
  }
  for (long p = 0; p < n; p++) {
    printf("%ld ", a[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/