// Problem: CF 505 B - Mr. Kitayuta's Colorful Graph
// https://codeforces.com/contest/505/problem/B

/*
Purpose: This program solves the problem of counting how many distinct colors
         connect two vertices in an undirected graph, using DFS traversal for
         each color separately.

Algorithms/Techniques:
- Graph representation using a 3D vector where g[c][u][v] indicates if edge
  exists between u and v with color c.
- For each query, we perform a DFS for each color to check connectivity
  between two nodes, counting the number of colors that connect them.

Time Complexity: O(q * m * n) where q is number of queries, m is number of edges,
                 and n is number of vertices. In worst case, for each query we
                 do dfs for all m colors and each DFS can take O(n) time.
Space Complexity: O(m * n^2) to store the adjacency matrix for each color,
                  and O(n) for the visited array during DFS.

*/
#include <stdio.h>
#include <vector>

// DFS to check if target is reachable from source using adjacency matrix h
bool dfs(const int &source, const int &target,
         std::vector<std::vector<bool>> &h, std::vector<bool> &visited) {
  if (visited[source] || source == target) {
    return true;
  }
  visited[source] = true;
  for (int p = 0; p < h.size(); p++) {
    if (visited[p] || !h[source][p]) {
      continue;
    }
    if (p == target) {
      return true;
    }
    int temp = dfs(p, target, h, visited);
    if (temp) {
      return true;
    }
  }
  return false;
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  // 3D vector to represent graph: g[color][node1][node2]
  std::vector<std::vector<std::vector<bool>>> g(
      m + 1,
      std::vector<std::vector<bool>>(n + 1, std::vector<bool>(n + 1, 0)));
  for (int p = 0; p < m; p++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    g[c][a][b] = g[c][b][a] = 1;  // Mark edge in both directions
  }
  int q;
  scanf("%d", &q);
  while (q--) {
    int u, v;
    scanf("%d %d", &u, &v);
    int count(0);
    for (int p = 1; p <= m; p++) {
      std::vector<bool> vis(n + 1, 0);
      count += dfs(u, v, g[p], vis);  // Check if nodes are connected via color p
    }
    printf("%d\n", count);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/