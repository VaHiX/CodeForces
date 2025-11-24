// Problem: CF 859 E - Desk Disorder
// https://codeforces.com/contest/859/problem/E

/*
 * Problem: E. Desk Disorder
 * Purpose: Calculate the number of valid seating arrangements for engineers
 *          based on their current and desired desk positions.
 * 
 * Algorithm:
 * - Model the problem as a graph where each engineer is connected to their desired desk.
 * - Each connected component in the graph represents a cycle or self-loop.
 * - For each component:
 *   - If it's a self-loop (a -> a), there is 1 way to assign (1 choice).
 *   - If it's a cycle of length k, there are 2 ways to assign (2 choices: clockwise or counter-clockwise).
 *   - If it's a tree-like structure, there is 1 way (only one valid assignment).
 * - Multiply all valid assignments together modulo 10^9 + 7.
 * 
 * Time Complexity: O(N + M) where N is number of engineers and M is number of edges (2*N)
 * Space Complexity: O(N) for graph storage and visited array
 */

#include <stdint.h>
#include <cstdio>
#include <vector>

void dfs(int64_t node, int64_t from, const std::vector<std::vector<int64_t>> &g,
         std::vector<bool> &visited, int64_t &count, bool &cycle, bool &self) {
  if (visited[node]) {
    return;
  }
  visited[node] = 1;
  ++count;
  for (int64_t p = 0; p < g[node].size(); p++) {
    int64_t u = g[node][p];
    if (u == from) {
      continue;
    } else if (u == node) {
      self = true;
    } else if (visited[u]) {
      cycle = true;
    } else {
      dfs(u, node, g, visited, count, cycle, self);
    }
  }
  return;
}

int main() {
  const int64_t MOD = 1000000007;
  int64_t n;
  scanf("%lld", &n);
  std::vector<std::vector<int64_t>> g(2 * n);
  for (int64_t p = 0; p < n; p++) {
    int64_t x, y;
    scanf("%lld %lld", &x, &y);
    --x;
    --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  std::vector<bool> visited(2 * n, false);
  int64_t total(1);
  for (int64_t p = 0; p < 2 * n; p++) {
    if (visited[p]) {
      continue;
    }
    int64_t count(0);
    bool cycle(false), self(false);
    dfs(p, -1, g, visited, count, cycle, self);
    if (self) {
      count = 1;
    } else if (cycle) {
      count = 2;
    }
    total *= count;
    total %= MOD;
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/