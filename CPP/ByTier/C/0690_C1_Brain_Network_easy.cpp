// Problem: CF 690 C1 - Brain Network (easy)
// https://codeforces.com/contest/690/problem/C1

/*
 * Problem: C1. Brain Network (easy)
 *
 * Purpose: Determine if a zombie's brain network is valid. A valid network must:
 *          1. Be connected (able to send thoughts between any two brains).
 *          2. Be minimally connected (no redundant edges - removing any edge breaks connectivity).
 *
 * Algorithm: 
 * - Check if the number of edges equals n - 1. If not, it's invalid (property 2).
 * - Perform DFS from node 1 to check if all nodes are reachable (property 1).
 * - If all nodes are visited, output "yes", otherwise "no".
 *
 * Time Complexity: O(n + m) - Standard DFS traversal
 * Space Complexity: O(n + m) - For adjacency list representation and visited array
 */

#include <cstdio>
#include <vector>
void dfs(long node, const std::vector<std::vector<long>> &g,
         std::vector<bool> &been, long &num) {
  if (been[node]) {
    return;
  }
  been[node] = 1;
  ++num;
  std::vector<long> adj = g[node];
  for (long p = 0; p < adj.size(); p++) {
    long next = adj[p];
    if (been[next]) {
      continue;
    }
    dfs(next, g, been, num);
  }
  return;
}
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  if (m != n - 1) {
    puts("no");
    return 0;
  }
  std::vector<std::vector<long>> g(n + 1);
  for (long p = 0; p < m; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  std::vector<bool> visited(n + 1, 0);
  long count(0);
  dfs(1, g, visited, count);
  puts((count >= n) ? "yes" : "no");
  return 0;
}


// https://github.com/VaHiX/CodeForces/