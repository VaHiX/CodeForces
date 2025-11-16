// Problem: CF 780 E - Underground Lab
// https://codeforces.com/contest/780/problem/E

/*
 * Problem: Underground Lab
 * Algorithm: Depth-First Search (DFS) to find an Eulerian path, then divide the path among k clones.
 * Time Complexity: O(n + m) - Linear time for DFS and splitting the path.
 * Space Complexity: O(n + m) - For storing the graph and recursion stack.
 *
 * Approach:
 * 1. Build the adjacency list representation of the graph.
 * 2. Perform a DFS traversal to generate a path that visits all edges and returns to the start.
 * 3. Adjust the path to ensure it's a valid Eulerian cycle.
 * 4. Split the resulting path into k segments, each of approximately equal length.
 * 5. Output each segment with appropriate formatting.
 */

#include <cstdio>
#include <vector>

void dfs(long node, long from, const std::vector<std::vector<long>> &g,
         std::vector<bool> &vis, std::vector<long> &path) {
  if (vis[node]) {
    return;
  }
  vis[node] = 1;
  path.push_back(node);
  for (long p = 0; p < g[node].size(); p++) {
    long u = g[node][p];
    if (vis[u]) {
      continue;
    }
    dfs(u, node, g, vis, path);
  }
  path.push_back(from); // Add backtracking to represent edge traversal
  return;
}

int main() {
  long n, m, k;
  scanf("%ld %ld %ld", &n, &m, &k);
  std::vector<std::vector<long>> g(n);
  for (long p = 0; p < m; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    --x;
    --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  std::vector<long> path;
  std::vector<bool> visited(n, 0);
  dfs(0, -1, g, visited, path);
  path.pop_back(); // Remove the last node (which is the same as the first due to backtracking)
  path.pop_back(); // Remove the second to last node (which is the same as the previous due to backtracking)
  
  long len = ((2 * n) / k) + (((2 * n) % k) > 0); // Calculate length for each clone's path
  long index(0);
  for (long p = 0; p < k; p++) {
    if (index + len < path.size()) {
      printf("%ld ", len);
      for (long q = 0; q < len; q++) {
        printf("%ld ", 1 + path[index]);
        ++index;
      }
    } else if (index == path.size()) {
      printf("1 1"); // Handle case where we have to print a single vertex
    } else {
      printf("%ld ", path.size() - index);
      while (index < path.size()) {
        printf("%ld ", 1 + path[index]);
        ++index;
      }
    }
    puts(""); // Print newline after each clone's path
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/